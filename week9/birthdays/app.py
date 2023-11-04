import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        # TODO: Add the user's entry into the database
        # come fare: prendi la variable date = request get blabla bla è una stringa, quindi  devi semplicemente fare date[da-a]
        date = request.form.get("date")
        name = request.form.get("name")
        if request.form['action'] == "Add Birthday":
            db.execute("INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)", name, date[5:7], date[8:])
            return redirect("/")
        elif request.form['action'] == "Delete last row":
            db.execute("DELETE FROM birthdays ORDER BY id DESC LIMIT 1")
            return redirect("/")
        elif request.form['action'] == "Delete All":
            db.execute("DELETE FROM birthdays")
            return redirect("/")

    else:

        # TODO: Display the entries in the database on index.html
        birthdays = db.execute("SELECT * FROM birthdays")
        return render_template("index.html", birthdays = birthdays)


