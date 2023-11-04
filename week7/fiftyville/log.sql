-- Keep a log of any SQL queries you execute as you solve the mystery.

-- first step to obtain the crime scene report id
SELECT *
FROM crime_scene_reports
where year = 2021 AND month = 7 AND day = 28 AND street = "Humphrey Street"; --Obtained the id of the crime report: 295
-- obtained also other info as three interviews in the same day

-- now I need to spot the three correct interviews
SELECT *
from interviews
where year = 2021 AND month = 7 and DAY = 28 AND transcript LIKE '%bakery%'; -- three interview ids: 161, 162, 163

-- need to check logs of the bakery park of that day, ATM withdraw, day after flight at the airport bought by accomplice also checking phone calls

--all useful logs of the bakery park close to the theft
SELECT *
FROM bakery_security_logs
WHERE day = 28 AND month = 7 AND year = 2021 AND hour = 10 AND activity = 'exit' AND minute >= 15 AND minute <= 25
ORDER BY minute;
-- the thief did everything in less whitin 10 minutes so I want to find the license plate thanks to this difference

-- check for ATM
SELECT * FROM atm_transactions
WHERE year = 2021 and month = 7 AND day = 28 and atm_location = 'Leggett Street' AND transaction_type = 'withdraw';

-- get the person_id to intersect it with the license plate, phone number and passport number
SELECT person_id FROM bank_accounts
WHERE account_number IN
(SELECT account_number FROM atm_transactions
WHERE year = 2021 and month = 7 AND day = 28 and atm_location = 'Leggett Street' AND transaction_type = 'withdraw');

-- check the airport name
SELECT id FROM airports
WHERE city = 'Fiftyville';

--now check flights in order bc he wants the earliest of the day after
SELECT * FROM flights
WHERE origin_airport_id =
(SELECT id FROM airports
WHERE city = 'Fiftyville')
and year = 2021 AND month = 7 and day = 29 ORDER BY hour, minute;

-- find the destination
SELECT city FROM airports
WHERE id =
(SELECT destination_airport_id FROM flights
WHERE origin_airport_id =
(SELECT id FROM airports
WHERE city = 'Fiftyville')
and year = 2021 AND month = 7 and day = 29 AND hour = 8 AND minute = 20);
-- city of destination is New York City

-- checking the passengers of the first flight
SELECT passengers.passport_number, people.name FROM passengers
JOIN people On passengers.passport_number = people.passport_number
WHERE flight_id =
(SELECT id FROM flights
WHERE origin_airport_id =
(SELECT id FROM airports
WHERE city = 'Fiftyville')
AND year = 2021 AND month = 7 AND day = 29 AND hour = 8 AND minute = 20);

-- phone call
SELECT caller FROM phone_calls
WHERE day = 28 AND month = 7 AND year = 2021 AND duration <= 60 ORDER BY duration;

-- intersect everything
select name, license_plate, passport_number, phone_number
FROM people
WHERE id IN
(SELECT person_id
FROM bank_accounts
WHERE account_number IN
(SELECT account_number
FROM atm_transactions
WHERE year = 2021 and month = 7 AND day = 28 and atm_location = 'Leggett Street' AND transaction_type = 'withdraw'))
AND license_plate IN
(SELECT license_plate FROM bakery_security_logs
WHERE day = 28 AND month = 7 AND year = 2021 AND hour = 10 AND activity = 'exit' AND minute >= 15 AND minute <= 25)
AND passport_number IN
(SELECT passengers.passport_number FROM passengers
JOIN people On passengers.passport_number = people.passport_number
WHERE flight_id = (SELECT id FROM flights
WHERE origin_airport_id = (SELECT id FROM airports WHERE city = 'Fiftyville')
AND year = 2021 AND month = 7 AND day = 29 AND hour = 8 AND minute = 20))
AND phone_number IN
(SELECT caller FROM phone_calls
WHERE day = 28 AND month = 7 AND year = 2021 AND duration <= 60);
-- Finally the culprit is Bruce.

-- finding the accomplice
SELECT name FROM people
WHERE phone_number =
(SELECT receiver FROM phone_calls
WHERE caller =
(SELECT phone_number FROM people
WHERE name = 'Bruce')
AND duration <= 60);
-- the accomplice is Robin