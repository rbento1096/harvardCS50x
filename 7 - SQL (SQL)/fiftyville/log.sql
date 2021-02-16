-- https://cs50.harvard.edu/x/2021/psets/7/fiftyville/
-- Keep a log of any SQL queries you execute as you solve the mystery.

-- What we know: theft took place on 28th of July of 2020, on Chamberlin Street

-- Read the crime scene report
SELECT description
FROM crime_scene_reports
WHERE year = 2020 AND month = 7 AND day = 28 AND street = "Chamberlin Street";
-- theft took place at 10:15 AM, three interviews were conducted on 28/7/2020, all interviews mention the courthouse

-- check interviews
SELECT name, transcript
FROM interviews
WHERE year = 2020 AND month = 7 AND day = 28;
-- Ruth: within 10 minutes of theft, a thief got into a car in the courthouse parking loft and drove away
-- Eugene: someone he recognized from earlier - he saw the thief withdrawing money from the Fifer Street ATM that morning (28/7/2020)
/* Raymond: as the thief left the courthouse, they called someone and talked for less than a minute.
They planned to take the earliest flight out of fiftyville the next day. The thief asked the accomplice to purchase a flight */

-- check courthouse logs
SELECT activity, license_plate
FROM courthouse_security_logs
WHERE  year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 15 AND 25;
-- 8 cars left at that time

-- check car owners
SELECT name
FROM people
WHERE license_plate IN(
    SELECT license_plate
    FROM courthouse_security_logs
    WHERE  year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 15 AND 25
);
-- Patrick, Amber, Elizabeth, Roger, Danielle, Russell, Evelyn, Ernest are all suspects

-- Who withdrew money that morning?
SELECT account_number
FROM atm_transactions
WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw";
-- 8 account numbers withdrew money

-- who owns these accounts?
SELECT name
FROM people
INNER JOIN bank_accounts
    ON people.id = bank_accounts.person_id
WHERE account_number IN(
    SELECT account_number
    FROM atm_transactions
    WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw"
);
-- Ernest, Russel, Roy, Bobby, Elizabeth, Danielle, Madison, Victoria withdrew money.
-- Crosschecking with the security logs, the suspects are now: Ernest, Russel, Elizabeth; Danielle

-- who called when leaving the courthouse for less than a minute and to whom
SELECT caller, receiver
FROM phone_calls
WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60;
-- We have 9 calls

-- Who called?
SELECT name
FROM people
WHERE phone_number IN(
    SELECT caller
    FROM phone_calls
    WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60
);
-- Bobby, Roger, Victoria, Madison, Russell, Evelyn, Ernest and Kimberly called
-- Crosschecking: Ernest, Russell are the suspects

-- Who received a call?
SELECT name, phone_number
FROM people
WHERE phone_number IN(
    SELECT receiver
    FROM phone_calls
    WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60
);
-- James, Larry, Anna, Jack, Melissa, Jacqueline, Philip, Berthold, Doris are the suspected accomplices

-- Earliest flight out of fiftyville?
SELECT city, hour
FROM flights
INNER JOIN airports
    ON destination_airport_id = airports.id
WHERE year = 2020 AND month = 7 AND day = 29 AND origin_airport_id = (
    SELECT id
    FROM airports
    WHERE city = "Fiftyville"
    )
ORDER BY hour
LIMIT 1;
-- They fled to London on the 8 AM flight!

-- Who, from the suspects was on it?
SELECT passport_number
FROM passengers
WHERE flight_id = (
    SELECT flights.id
    FROM flights
    INNER JOIN airports
        ON destination_airport_id = airports.id
    WHERE year = 2020 AND month = 7 AND day = 29 AND origin_airport_id = (
        SELECT id
        FROM airports
        WHERE city = "Fiftyville"
        )
ORDER BY hour
LIMIT 1
);
-- We get 8 passport numbers

-- Who own these passports?
SELECT name
FROM people
WHERE passport_number IN (
    SELECT passport_number
    FROM passengers
    WHERE flight_id = (
        SELECT flights.id
        FROM flights
        INNER JOIN airports
            ON destination_airport_id = airports.id
        WHERE year = 2020 AND month = 7 AND day = 29 AND origin_airport_id = (
            SELECT id
            FROM airports
            WHERE city = "Fiftyville"
            )
    ORDER BY hour
    LIMIT 1
    )
);
-- We get: Bobby, Roger, Madison, Danielle, Evelyn, Edward, Ernest, Doris
-- Crosschecking with previous suspects: Ernest is the thief!
-- If we were to assume the accomplice went with him, Doris would be the accomplice... But let's check who Ernest called the previous day!

-- Who did Ernest call?
SELECT name
FROM people
WHERE phone_number = (
    SELECT receiver
    FROM phone_calls
    WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60 AND caller = (
        SELECT phone_number
        FROM people
        WHERE name ="Ernest"
    )
);
-- Ernest called Berthold! So he is the accomplice.