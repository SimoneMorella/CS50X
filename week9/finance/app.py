import os
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime
from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    row = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
    name = row[0]["username"]
    cash = float(row[0]["cash"])
    portfolio_rows = db.execute("SELECT * FROM purchase WHERE owner = ?", name)
    if not portfolio_rows:
        total = cash
        return render_template("index.html", cash=cash, total=total)

    else:
        for row in portfolio_rows:
            dict = lookup(row["Symbol"])
            row["Price"] = dict["price"]
            db.execute(
                "UPDATE purchase SET Price = ?, Total = ? WHERE Symbol = ? AND owner = ?",
                float(row["Price"]),
                float(row["Price"]) * row["Shares"],
                row["Symbol"],
                name,
            )

        sum = db.execute("SELECT SUM(Total) AS sum FROM purchase WHERE owner = ?", name)
        total = float(cash + sum[0]["sum"])
        return render_template(
            "index.html", portfolio_rows=portfolio_rows, cash=cash, total=total
        )


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol").upper()
        shares = request.form.get("shares")
        dict = lookup(symbol)
        row = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
        name = row[0]["username"]
        cash = row[0]["cash"]

        if (
            not symbol
            or not shares
            or not dict
            or not shares.isnumeric()
            or int(shares) < 1
        ):
            return apology("Insert a valid symbol and/or a valid number", 400)

        else:
            if (int(shares) * float(dict["price"])) > cash:
                return apology("Not enough cash to complete the transaction")

            else:
                purchase = db.execute(
                    "SELECT * FROM purchase WHERE Symbol = ? AND owner = ?",
                    symbol,
                    name,
                )
                if not purchase:
                    db.execute(
                        "INSERT INTO purchase (Symbol, Name, Shares, Price, Total, owner) VALUES (?, ?, ?, ?, ?, ?)",
                        symbol,
                        symbol,
                        float(shares),
                        int(dict["price"]),
                        float(dict["price"]) * int(shares),
                        name,
                    )
                    cash -= int(shares) * float(dict["price"])
                    db.execute(
                        "UPDATE users SET cash = ? WHERE id = ?",
                        cash,
                        session["user_id"],
                    )
                    now = datetime.now()
                    date_time = now.strftime("%m/%d/%Y, %H:%M:%S")
                    db.execute(
                        "INSERT INTO history (symbol, price, shares, type, owner, datetime) VALUES (?, ?, ?,'Buy', ?, ?)",
                        symbol,
                        float(dict["price"]),
                        int(shares),
                        name,
                        date_time,
                    )

                else:
                    db.execute(
                        "UPDATE purchase SET Shares = ?, Total = ? WHERE Symbol = ? AND owner = ?",
                        int(shares) + int(purchase[0]["Shares"]),
                        (int(shares) + int(purchase[0]["Shares"]))
                        * float(dict["price"]),
                        symbol,
                        name,
                    )
                    cash -= int(shares) * float(dict["price"])
                    db.execute(
                        "UPDATE users SET cash = ? WHERE id = ?",
                        cash,
                        session["user_id"],
                    )
                    now = datetime.now()
                    date_time = now.strftime("%m/%d/%Y, %H:%M:%S")
                    db.execute(
                        "INSERT INTO history (symbol, price, shares, type, owner, datetime) VALUES (?, ?, ?,'Buy', ?, ?)",
                        symbol,
                        float(dict["price"]),
                        int(shares),
                        name,
                        date_time,
                    )
                return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    row = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
    name = row[0]["username"]
    history_lines = db.execute("SELECT * FROM history WHERE owner = ?", name)

    return render_template("history.html", history_lines=history_lines)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol or not lookup(symbol):
            return apology("Insert a valid symbol")
        quote_dict = lookup(symbol)
        return render_template("quoted.html", quote_dict=quote_dict)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if not username or not password or not confirmation:
            return apology("Missing Username or Password")

        elif db.execute("SELECT * FROM users WHERE username = ?", username):
            return apology("This username already exists")

        elif password != confirmation:
            return apology("the password does not match")

        else:
            hash = generate_password_hash(password, "pbkdf2", 16)
            db.execute(
                "INSERT INTO users (username, hash) VALUES (?, ?)", username, hash
            )
            return render_template("reg_success.html")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    row = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
    name = row[0]["username"]
    cash = row[0]["cash"]
    entries = db.execute("SELECT Symbol, Shares FROM purchase WHERE owner = ?", name)
    if request.method == "POST":
        selected = request.form.get("symbol")
        shares = int(request.form.get("shares"))
        stock = db.execute(
            "SELECT Shares, Price FROM purchase WHERE Symbol = ? AND owner = ?",
            selected,
            name,
        )
        symbol_list = []

        for entry in entries:
            symbol_list.append(entry["Symbol"])

        if not selected or selected not in symbol_list:
            return apology("Symbol not valid")

        if int(stock[0]["Shares"]) == 0 or not stock[0]["Shares"] or shares < 1:
            return apology("No shares found")

        elif int(stock[0]["Shares"]) < shares:
            return apology("Not enough shares to sell")

        else:
            if shares == stock[0]["Shares"]:
                db.execute(
                    "DELETE FROM purchase WHERE Symbol = ? AND owner = ?",
                    selected,
                    name,
                )
                db.execute(
                    "UPDATE users SET cash = ? WHERE id = ?",
                    cash + (shares * stock[0]["Price"]),
                    session["user_id"],
                )
                now = datetime.now()
                date_time = now.strftime("%m/%d/%Y, %H:%M:%S")
                db.execute(
                    "INSERT INTO history (symbol, price, shares, type, owner, datetime) VALUES (?, ?, ?,'Sell', ?, ?)",
                    selected,
                    stock[0]["Price"],
                    int(shares),
                    name,
                    date_time,
                )
            elif shares < stock[0]["Shares"]:
                db.execute(
                    "UPDATE purchase SET Shares = ?, Total = ? WHERE Symbol = ? AND owner = ?",
                    stock[0]["Shares"] - shares,
                    (stock[0]["Shares"] - shares) * stock[0]["Price"],
                    selected,
                    name,
                )
                db.execute(
                    "UPDATE users SET cash = ? WHERE id = ?",
                    cash + (shares * stock[0]["Price"]),
                    session["user_id"],
                )
                now = datetime.now()
                date_time = now.strftime("%m/%d/%Y, %H:%M:%S")
                db.execute(
                    "INSERT INTO history (symbol, price, shares, type, owner, datetime) VALUES (?, ?, ?,'Sell', ?, ?)",
                    selected,
                    stock[0]["Price"],
                    int(shares),
                    name,
                    date_time,
                )

            return redirect("/")

    else:
        return render_template("sell.html", entries=entries)


@app.route("/credit", methods=["GET", "POST"])
@login_required
def credit():
    """add cash to the user"""
    row = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
    cash = row[0]["cash"]
    if request.method == "GET":
        alarm_bool = False
        message = " "
        return render_template("credit.html", message=message)
    else:
        added_cash = request.form.get("added_cash")
        if not added_cash:
            return apology("Insert a valid number")
        db.execute(
            "UPDATE users SET cash = ? WHERE id = ?",
            (float(cash) + float(added_cash)),
            session["user_id"],
        )
        alarm_bool = True
        if alarm_bool:
            message = "Cash added successfully!"
        return render_template("credit.html", message=message)
