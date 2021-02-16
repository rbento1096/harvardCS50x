/*In 10.sql, write a SQL query to list the names of all people who have directed a movie that received a rating of at least 9.0.
Your query should output a table with a single column for the name of each person.*/

SELECT DISTINCT name
FROM people
INNER JOIN directors
    ON people.id=directors.person_id
INNER JOIN ratings
    ON directors.movie_id=ratings.movie_id
WHERE rating >= 9.0;