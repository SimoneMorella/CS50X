SELECT AVG(rating) as Average
FROM ratings
WHERE movie_id IN
(SELECT id FROM movies WHERE year = 2012);