z
-- PART 1 
-- -----------------------------------------------------
-- EXERCICI 1
-- SELECT * FROM staff;
-- SELECT staff_id, fname, lname, salary FROM staff;    
-- SELECT staff_id, salary AS salari_mensual FROM staff; 

-- EXERCICI 2
-- SELECT DISTINCT property_id FROM viewing;   

-- EXERCICI 3
-- SELECT * FROM staff WHERE salary > 10000;     
-- SELECT street, city FROM branch WHERE city='London' OR city='Glasgow'; 
-- SELECT fname, lname, position, salary FROM staff WHERE salary>=10000 AND salary<=30000; 
-- SELECT fname, lname, position, salary FROM staff WHERE salary BETWEEN 10000 AND 30000; 
-- SELECT fname, lname, position FROM staff WHERE position IN('Manager', 'Supervisor'); 
-- SELECT * FROM privateowner WHERE address LIKE '%Glasgow%'; 
-- SELECT client_id, property_id, viewdate FROM viewing WHERE comment IS NULL; 

-- EXERCICI 4
-- SELECT * FROM staff ORDER BY salary DESC;
-- SELECT * FROM property4rent ORDER BY type ASC;
-- SELECT * FROM property4rent ORDER BY type ASC, rent ASC;

-- EXERCICI 5
-- SELECT COUNT(*) FROM property4rent WHERE rent > 450;
-- SELECT COUNT(DISTINCT property_id) FROM viewing WHERE viewdate BETWEEN '2016-03-01' AND '2016-04-30';
-- SELECT COUNT(*) AS total_managers, SUM(salary) AS salari_managers FROM staff WHERE position='Manager';
-- SELECT MIN(salary) AS salari_min, MAX(salary) AS salari_max, AVG(salary) as salari_avg FROM staff;

-- EXERCICI 6
-- SELECT * FROM property4rent WHERE city='Aberdeen';
-- INSERT INTO property4rent
-- (property_id, street, city, postcode, type, rooms, rent, owner_id, staff_id, branch_id)
-- VALUES
-- ('PA15', '12 Holhead', 'Aberdeen', 'AB7 5SU', 'House', 6, 600, 'CO99', 'SA9', 'B007'),
-- ('PA16', '14 Holhead', 'Aberdeen', 'AB7 5SU', 'House', 6, 600, 'CO99', 'SA9', 'B007'); 
-- SELECT * FROM property4rent WHERE city='Aberdeen';

-- EXERCICI 7
/*
UPDATE property4rent
SET rooms = 5, rent = 550
WHERE owner_id = 'CO99';
*/
-- SELECT * FROM property4rent WHERE city='Aberdeen';
/*
UPDATE privateOwner
SET telnumber = 1414444441, address = '14 Fergus Dr, Aberdeen AB2 7SX'
WHERE fname = 'Jack' AND lname='Dew';
*/
-- SELECT * FROM privateOwner;
/*
UPDATE property4rent
SET rent = rent*1.25
WHERE city = 'Glasgow';
*/

-- EXERCICI 8
-- DELETE FROM property4rent WHERE property_id = 'PA16';
-- SELECT * FROM property4rent WHERE city = 'Aberdeen';

-- -------------------------------------------------------
-- PART 2
-- -------------------------------------------------------

-- EXERCICI 9
/*
SELECT branch_id,
ROUND(AVG(salary), 0) AS Average_salary,
GROUP_CONCAT(" '", staff_id, "'") AS Employees
FROM staff
GROUP BY branch_id;
*/
-- SELECT * FROM property4rent;
/*
SELECT owner_id, SUM(rent) AS Total_rent FROM property4rent 
GROUP BY owner_id;
*/
-- SELECT branch_id, ROUND(SUM(salary), 2) AS Salary_add, COUNT(*) AS Total_employees FROM staff 
-- GROUP BY branch_id;
/*
    SELECT branch_id,GROUP_CONCAT(CONCAT("'", lname, "'") SEPARATOR ', ') AS Employees_last_name, MIN(salary) AS Min_salary FROM staff 
    GROUP BY branch_id
    HAVING Min_salary>=10000;
*/
/*
	SELECT owner_id, SUM(rent) AS Total_rent,  GROUP_CONCAT(DISTINCT CONCAT("'",city, "'") SEPARATOR ', ') AS Cities FROM property4rent 
    GROUP BY owner_id
    HAVING Total_rent>400
    ORDER BY owner_id DESC;
*/
   
-- EXERCICI 10
-- SELECT * FROM viewing;
-- SELECT * FROM viewing WHERE property_id IN(SELECT property_id FROM property4rent WHERE city !='Glasgow');
-- SELECT * FROM property4rent WHERE staff_id IN(SELECT staff_id FROM staff WHERE branch_id IN(SELECT branch_id FROM branch WHERE city = 'Glasgow'));
-- SELECT fname, lname, position, ROUND(salary-(SELECT AVG(salary) FROM staff)) AS Diff_AVG_Salary FROM staff WHERE salary > (SELECT AVG(salary) FROM staff);

-- EXERCICI 11
-- SELECT * FROM staff WHERE salary >= ANY(SELECT salary FROM staff WHERE branch_id IN(SELECT branch_id FROM branch WHERE city = 'Glasgow'));
-- SELECT * FROM staff WHERE salary > ALL(SELECT salary FROM staff WHERE branch_id IN(SELECT branch_id FROM branch WHERE city = 'Glasgow'));

-- EXERCICI 12
/*
START TRANSACTION;

DELETE FROM branch
WHERE branch_id = 'B005';

SELECT * FROM branch;

ROLLBACK;
*/
-- SELECT * FROM branch;

-- EXERCICI 13
/*
CREATE VIEW comp_staff AS 
SELECT staff_id, position, salary, branch_id FROM staff;

SELECT * FROM comp_staff;
*/

-- DROP VIEW comp_staff;

-- EXERCICI 14
-- SELECT * FROM property4rent AS Properties;

