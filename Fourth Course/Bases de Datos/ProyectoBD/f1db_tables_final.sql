SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';

DROP SCHEMA IF EXISTS `f1db`;
CREATE SCHEMA IF NOT EXISTS `f1db` DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;
USE f1db;

-- CIRCUITS
CREATE TABLE IF NOT EXISTS `f1db`.`circuits` (
  `circuitId` INT NOT NULL,
  `name` VARCHAR(255) NOT NULL,
  `location` VARCHAR(255),
  `country` VARCHAR(255),
  `latitude` FLOAT,
  `longitude` FLOAT,
  `altitude` INT,
  CONSTRAINT `circuit_pkey` PRIMARY KEY (`circuitId`)
);

-- CONSTRUCTORS
CREATE TABLE IF NOT EXISTS `f1db`.`constructors` (
  `constructorId` INT NOT NULL,
  `name` VARCHAR(255) NOT NULL,
  `nationality` VARCHAR(255),
  CONSTRAINT `constructor_pkey` PRIMARY KEY (`constructorId`)
);

-- DRIVERS
CREATE TABLE IF NOT EXISTS `f1db`.`drivers` (
  `driverId` INT NOT NULL,
  `number` INT,
  `code` VARCHAR(3),
  `forename` VARCHAR(255) NOT NULL,
  `surname` VARCHAR(255) NOT NULL,
  `dob` DATE,
  `nationality` VARCHAR(255),
  CONSTRAINT `driver_pkey` PRIMARY KEY (`driverId`)
);

-- RACES
CREATE TABLE IF NOT EXISTS `f1db`.`races` (
  `raceId` INT NOT NULL,
  `year` INT NOT NULL,
  `round` INT NOT NULL,
  `circuitId` INT NOT NULL,
  `name` VARCHAR(255) NOT NULL,
  `date` DATE,
  `time` TIME,
  CONSTRAINT `race_pkey` PRIMARY KEY (`raceId`)
);

-- DRIVER STANDINGS
CREATE TABLE IF NOT EXISTS `f1db`.`driverStandings` (
  `raceId` INT NOT NULL,
  `driverId` INT NOT NULL,
  `points` FLOAT NOT NULL DEFAULT 0,
  `position` INT,
  `positionText` VARCHAR(255),
  `wins` INT DEFAULT 0
);

-- CONSTRUCTOR STANDINGS
CREATE TABLE IF NOT EXISTS `f1db`.`constructorStandings` (
  `raceId` INT NOT NULL,
  `constructorId` INT NOT NULL,
  `points` FLOAT NOT NULL DEFAULT 0,
  `position` INT,
  `positionText` VARCHAR(255),
  `wins` INT DEFAULT 0
);

-- RESULTS
CREATE TABLE IF NOT EXISTS `f1db`.`results` (
  `resultId` INT NOT NULL,
  `raceId` INT NOT NULL,
  `driverId` INT NOT NULL,
  `constructorId` INT NOT NULL,
  `number` INT,
  `grid` INT,
  `position` INT,
  `positionText` VARCHAR(255),
  `points` FLOAT,
  `laps` INT,
  `time` VARCHAR(255),
  `milliseconds` INT,
  `fastestLap` INT,
  `rank` INT,
  `fastestLapTime` VARCHAR(255),
  `fastestLapSpeed` VARCHAR(255),
  CONSTRAINT `results_pkey` PRIMARY KEY (`resultId`)
);

-- SPRINT RESULTS
CREATE TABLE IF NOT EXISTS `f1db`.`sprintResults` (
  `sprintResultId` INT NOT NULL,
  `raceId` INT NOT NULL,
  `driverId` INT NOT NULL,
  `constructorId` INT NOT NULL,
  `number` INT,
  `grid` INT,
  `position` INT,
  `positionText` VARCHAR(255),
  `points` FLOAT,
  `laps` INT,
  `time` VARCHAR(255),
  `milliseconds` INT,
  `fastestLap` INT,
  `fastestLapTime` VARCHAR(255),
  CONSTRAINT `sprintresults_pkey` PRIMARY KEY (`sprintResultId`)
);

-- LAP TIMES
CREATE TABLE IF NOT EXISTS `f1db`.`lapTimes` (
  `raceId` INT NOT NULL,
  `driverId` INT NOT NULL,
  `lap` INT NOT NULL,
  `position` INT,
  `time` VARCHAR(255),
  `milliseconds` INT,
  CONSTRAINT `laptimes_pkey` PRIMARY KEY (`raceId`, `driverId`, `lap`)
);

-- CLAVES FORÁNEAS

ALTER TABLE `f1db`.`races`
  ADD CONSTRAINT `races_fk_circuit` FOREIGN KEY (`circuitId`) REFERENCES `f1db`.`circuits` (`circuitId`) ON DELETE CASCADE;

ALTER TABLE `f1db`.`driverStandings`
  ADD CONSTRAINT `ds_fk_race` FOREIGN KEY (`raceId`) REFERENCES `f1db`.`races` (`raceId`) ON DELETE CASCADE,
  ADD CONSTRAINT `ds_fk_driver` FOREIGN KEY (`driverId`) REFERENCES `f1db`.`drivers` (`driverId`);

ALTER TABLE `f1db`.`constructorStandings`
  ADD CONSTRAINT `cs_fk_race` FOREIGN KEY (`raceId`) REFERENCES `f1db`.`races` (`raceId`) ON DELETE CASCADE,
  ADD CONSTRAINT `cs_fk_constructor` FOREIGN KEY (`constructorId`) REFERENCES `f1db`.`constructors` (`constructorId`);

ALTER TABLE `f1db`.`results`
  ADD CONSTRAINT `results_fk_race` FOREIGN KEY (`raceId`) REFERENCES `f1db`.`races` (`raceId`) ON DELETE CASCADE,
  ADD CONSTRAINT `results_fk_driver` FOREIGN KEY (`driverId`) REFERENCES `f1db`.`drivers` (`driverId`),
  ADD CONSTRAINT `results_fk_constructor` FOREIGN KEY (`constructorId`) REFERENCES `f1db`.`constructors` (`constructorId`);

ALTER TABLE `f1db`.`sprintResults`
  ADD CONSTRAINT `sprint_fk_race` FOREIGN KEY (`raceId`) REFERENCES `f1db`.`races` (`raceId`) ON DELETE CASCADE,
  ADD CONSTRAINT `sprint_fk_driver` FOREIGN KEY (`driverId`) REFERENCES `f1db`.`drivers` (`driverId`),
  ADD CONSTRAINT `sprint_fk_constructor` FOREIGN KEY (`constructorId`) REFERENCES `f1db`.`constructors` (`constructorId`);

ALTER TABLE `f1db`.`lapTimes`
  ADD CONSTRAINT `laptime_fk_race` FOREIGN KEY (`raceId`) REFERENCES `f1db`.`races` (`raceId`) ON DELETE CASCADE,
  ADD CONSTRAINT `laptime_fk_driver` FOREIGN KEY (`driverId`) REFERENCES `f1db`.`drivers` (`driverId`);


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;