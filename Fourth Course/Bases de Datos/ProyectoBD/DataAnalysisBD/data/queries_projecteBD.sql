-- GRAN PREMI AMB FINAL MÉS JUST ENTRE PRIMER I SEGON CLASSIFICAT

-- Query per crear vista R_TOP2
DROP VIEW IF EXISTS R_TOP2;

CREATE VIEW R_TOP2 AS
SELECT 
	*
FROM 
	results
WHERE 
	position = 1 OR position = 2
ORDER BY 
	raceId ASC;

-- Query per crear vista FINAL_JUST
DROP VIEW IF EXISTS FINAL_JUST;

CREATE VIEW FINAL_JUST AS
SELECT 
	R1.raceId,
	R1.driverId AS driver1,
	R1.milliseconds AS temps1,
	R2.driverId AS driver2,
	R2.milliseconds AS temps2
FROM 
	R_TOP2 AS R1
JOIN 
	R_TOP2 AS R2 
	ON R1.raceId = R2.raceId
WHERE 
	R1.position = 1 
AND 
	R2.position = 2
ORDER BY 
	R1.raceId ASC;

-- Query per crear vista DIF_TEMPS
DROP VIEW IF EXISTS DIF_TEMPS;

CREATE VIEW DIF_TEMPS AS
SELECT 
	raceId, 
	(temps2 - temps1) AS dif_temps
FROM 
	FINAL_JUST
ORDER BY 
	raceId ASC;

-- Query per crear vista MIN_DIF
DROP VIEW IF EXISTS MIN_DIF;

CREATE VIEW MIN_DIF AS
SELECT 
	R2.name, 
	R2.date 
FROM 
	DIF_TEMPS AS R1
INNER JOIN 
	races AS R2 
	ON R1.raceId = R2.raceId
WHERE 
	R1.dif_temps = (
	SELECT MIN(dif_temps)
	FROM DIF_TEMPS
);

-- PUNTUACIÓ DELS DIFERENTS EQUIPS PER CADA ANY

-- Query per crear vista GP_1994
DROP VIEW IF EXISTS GP_1994;

CREATE VIEW GP_1994 AS
SELECT 
	*
FROM 
	races
WHERE 
	year >= 1994
ORDER BY 
	year ASC;

-- Query per crear vista RESULTATS_1994
DROP VIEW IF EXISTS RESULTATS_1994;

CREATE VIEW RESULTATS_1994 AS
SELECT 
	R2.*,
	R1.driverId,
	R1.constructorId,
	R1.points
FROM 
	results AS R1
INNER JOIN 
	GP_1994 AS R2 
	ON R1.raceId = R2.raceId
ORDER BY 
	year ASC;
	
-- Query per crear vista RES_CONST
DROP VIEW IF EXISTS RES_CONST;

CREATE VIEW RES_CONST AS
SELECT 
	R2.*,
	R1.name AS constructor_name,
	R1.nationality
FROM 
	constructors AS R1
INNER JOIN 
	RESULTATS_1994 AS R2 
	ON R1.constructorId = R2.constructorId
ORDER BY 
	year ASC;

-- Query per crear vista PUNTS_CONST
DROP VIEW IF EXISTS PUNTS_CONST;

CREATE VIEW PUNTS_CONST AS
SELECT 
	constructorId,
	constructor_name,
	year,
	SUM(points) AS total_points
FROM 
	RES_CONST
GROUP BY 
	constructorId, 
	year
ORDER BY 
	year ASC;
	
-- PUNTUACIÓ DELS DIFERENTS PILOTS PER CADA ANY

-- Per aquesta consulta, s'utilitzen les anteriors vistes GP_1994 i RESULTATS_1994

-- Query per crear vista RES_PILOTS
DROP VIEW IF EXISTS RES_PILOTS; 

CREATE VIEW RES_PILOTS AS
SELECT 
	R2.*, 
	R1.code, 
	R1.forename, 
	R1.surname, 
	R1.nationality 
FROM 
	drivers AS R1 
INNER JOIN
	RESULTATS_1994 AS R2 
	ON R1.driverId = R2.driverId
ORDER BY 
	year ASC;

-- Query per crear vista PUNTS_PILOTS
DROP VIEW IF EXISTS PUNTS_PILOTS;

CREATE VIEW PUNTS_PILOTS AS
SELECT 
	constructorId, 
	year, 
	driverId, 
	forename, 
	surname, 
	SUM(points) AS total_points, 
	COUNT(driverId) AS num_races
FROM 
	RES_PILOTS
GROUP BY 
	constructorId, 
	year, 
	driverId
ORDER BY 
	year ASC;
