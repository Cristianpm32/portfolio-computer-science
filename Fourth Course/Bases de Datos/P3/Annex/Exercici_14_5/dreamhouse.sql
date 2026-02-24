-- MySQL dump 10.13  Distrib 8.0.42, for macos15.2 (arm64)
--
-- Host: localhost    Database: dreamhouse
-- ------------------------------------------------------
-- Server version	8.0.42

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `branch`
--

DROP TABLE IF EXISTS `branch`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `branch` (
  `branch_id` varchar(5) COLLATE utf8mb3_unicode_ci NOT NULL,
  `street` varchar(25) COLLATE utf8mb3_unicode_ci NOT NULL,
  `city` varchar(15) COLLATE utf8mb3_unicode_ci NOT NULL,
  `postcode` varchar(10) COLLATE utf8mb3_unicode_ci NOT NULL,
  PRIMARY KEY (`branch_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `branch`
--

LOCK TABLES `branch` WRITE;
/*!40000 ALTER TABLE `branch` DISABLE KEYS */;
INSERT INTO `branch` VALUES ('B002','56 Clover Dr','London','NW10 6EU'),('B003','163 Main St','Glasgow','G11 9QX'),('B004','32 Manse Rd','Bristol','BS99 1NZ'),('B005','22 Deer Rd','London','SW1 4EH'),('B007','16 Argyll St','Aberdeen','AB2 3SU');
/*!40000 ALTER TABLE `branch` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `client`
--

DROP TABLE IF EXISTS `client`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `client` (
  `client_id` varchar(5) COLLATE utf8mb3_unicode_ci NOT NULL,
  `fname` varchar(10) COLLATE utf8mb3_unicode_ci NOT NULL,
  `lname` varchar(10) COLLATE utf8mb3_unicode_ci NOT NULL,
  `telnumber` decimal(10,0) NOT NULL,
  `pref_type` varchar(8) COLLATE utf8mb3_unicode_ci NOT NULL,
  `max_rent` decimal(10,0) NOT NULL,
  PRIMARY KEY (`client_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `client`
--

LOCK TABLES `client` WRITE;
/*!40000 ALTER TABLE `client` DISABLE KEYS */;
INSERT INTO `client` VALUES ('CR56','Aline','Stewart',1418481825,'Flat',350),('CR62','Mary','Tregear',1224196720,'Flat',600),('CR74','Mike','Ritchie',1475392178,'House',750),('CR76','John','Kay',2077745632,'Flat',425);
/*!40000 ALTER TABLE `client` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `privateowner`
--

DROP TABLE IF EXISTS `privateowner`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `privateowner` (
  `privateowner_id` varchar(5) COLLATE utf8mb3_unicode_ci NOT NULL,
  `fname` varchar(10) COLLATE utf8mb3_unicode_ci NOT NULL,
  `lname` varchar(10) COLLATE utf8mb3_unicode_ci NOT NULL,
  `address` varchar(50) COLLATE utf8mb3_unicode_ci NOT NULL,
  `telnumber` decimal(10,0) NOT NULL,
  PRIMARY KEY (`privateowner_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `privateowner`
--

LOCK TABLES `privateowner` WRITE;
/*!40000 ALTER TABLE `privateowner` DISABLE KEYS */;
INSERT INTO `privateowner` VALUES ('CO40','Tina','Murphy','63 Well St, Glasgow G42',1419431728),('CO46','Joe','Keogh','2 Fergus Dr, Aberdeen AB2 7SX',1224861212),('CO87','Carol','Farrel','6 Achray St, Glasgow G32 9DX',1413577419),('CO93','Tony','Shaw','12 Park Pl, Glasgow G4 0QR',1412257025);
/*!40000 ALTER TABLE `privateowner` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `property4rent`
--

DROP TABLE IF EXISTS `property4rent`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `property4rent` (
  `property_id` varchar(5) COLLATE utf8mb3_unicode_ci NOT NULL,
  `street` varchar(25) COLLATE utf8mb3_unicode_ci NOT NULL,
  `city` varchar(15) COLLATE utf8mb3_unicode_ci NOT NULL,
  `postcode` varchar(10) COLLATE utf8mb3_unicode_ci NOT NULL,
  `type` varchar(8) COLLATE utf8mb3_unicode_ci NOT NULL,
  `rooms` decimal(10,0) NOT NULL,
  `rent` decimal(10,0) NOT NULL,
  `owner_id` varchar(5) COLLATE utf8mb3_unicode_ci NOT NULL,
  `staff_id` varchar(5) COLLATE utf8mb3_unicode_ci DEFAULT NULL,
  `branch_id` varchar(5) COLLATE utf8mb3_unicode_ci NOT NULL,
  PRIMARY KEY (`property_id`),
  KEY `owner_FK_property` (`owner_id`),
  KEY `staff_FK_property` (`staff_id`),
  KEY `branch_FK_property` (`branch_id`),
  CONSTRAINT `branch_FK_property` FOREIGN KEY (`branch_id`) REFERENCES `branch` (`branch_id`) ON DELETE CASCADE,
  CONSTRAINT `owner_FK_property` FOREIGN KEY (`owner_id`) REFERENCES `privateowner` (`privateowner_id`),
  CONSTRAINT `staff_FK_property` FOREIGN KEY (`staff_id`) REFERENCES `staff` (`staff_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `property4rent`
--

LOCK TABLES `property4rent` WRITE;
/*!40000 ALTER TABLE `property4rent` DISABLE KEYS */;
INSERT INTO `property4rent` VALUES ('PA14','16 Holhead','Aberdeen','AB7 5SU','House',6,650,'CO46','SA9','B007'),('PG16','5 Novar Dr','Glasgow','G12 9AX','Flat',4,450,'CO93','SG14','B003'),('PG21','18 Dale Rd','Glasgow','G12','House',5,600,'CO87','SG37','B003'),('PG36','2 Manor Rd','Glasgow','G32 4QX','Flat',3,375,'CO93','SG37','B003'),('PG4','6 Lawrence St','Glasgow','G11 9QX','Flat',3,350,'CO40',NULL,'B003'),('PL94','6 Argyll St','London','NW2','Flat',4,400,'CO87','SL41','B005');
/*!40000 ALTER TABLE `property4rent` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `registration`
--

DROP TABLE IF EXISTS `registration`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `registration` (
  `client_id` varchar(5) COLLATE utf8mb3_unicode_ci NOT NULL,
  `branch_id` varchar(5) COLLATE utf8mb3_unicode_ci NOT NULL,
  `staff_id` varchar(5) COLLATE utf8mb3_unicode_ci NOT NULL,
  `date_joined` date NOT NULL,
  PRIMARY KEY (`client_id`,`branch_id`),
  KEY `branch_FK_registration` (`branch_id`),
  KEY `staff_FK_registration` (`staff_id`),
  CONSTRAINT `branch_FK_registration` FOREIGN KEY (`branch_id`) REFERENCES `branch` (`branch_id`) ON DELETE CASCADE,
  CONSTRAINT `client_FK_registration` FOREIGN KEY (`client_id`) REFERENCES `client` (`client_id`),
  CONSTRAINT `staff_FK_registration` FOREIGN KEY (`staff_id`) REFERENCES `staff` (`staff_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `registration`
--

LOCK TABLES `registration` WRITE;
/*!40000 ALTER TABLE `registration` DISABLE KEYS */;
INSERT INTO `registration` VALUES ('CR56','B003','SG37','2003-04-11'),('CR62','B007','SA9','2003-03-04'),('CR74','B003','SG37','2002-04-16'),('CR76','B005','SL41','2004-01-02');
/*!40000 ALTER TABLE `registration` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `staff`
--

DROP TABLE IF EXISTS `staff`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `staff` (
  `staff_id` varchar(5) COLLATE utf8mb3_unicode_ci NOT NULL,
  `fname` varchar(10) COLLATE utf8mb3_unicode_ci NOT NULL,
  `lname` varchar(10) COLLATE utf8mb3_unicode_ci NOT NULL,
  `position` varchar(15) COLLATE utf8mb3_unicode_ci NOT NULL,
  `sex` char(1) COLLATE utf8mb3_unicode_ci NOT NULL,
  `dob` date NOT NULL,
  `salary` decimal(10,0) NOT NULL,
  `branch_id` varchar(5) COLLATE utf8mb3_unicode_ci NOT NULL,
  PRIMARY KEY (`staff_id`),
  KEY `staff_FK_staff` (`branch_id`),
  CONSTRAINT `staff_FK_staff` FOREIGN KEY (`branch_id`) REFERENCES `branch` (`branch_id`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `staff`
--

LOCK TABLES `staff` WRITE;
/*!40000 ALTER TABLE `staff` DISABLE KEYS */;
INSERT INTO `staff` VALUES ('SA9','Mary','Howe','Assistant','F','1970-02-19',9000,'B007'),('SG14','David','Ford','Supervisor','M','1958-03-24',18000,'B003'),('SG37','Ann','Beech','Assistant','F','1960-11-10',12000,'B003'),('SG5','Susan','Brand','Manager','F','1955-06-03',24000,'B003'),('SL21','John','White','Manager','M','1950-10-01',30000,'B005'),('SL41','Julie','Lee','Assistant','F','1965-06-13',9000,'B005');
/*!40000 ALTER TABLE `staff` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `viewing`
--

DROP TABLE IF EXISTS `viewing`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `viewing` (
  `client_id` varchar(5) COLLATE utf8mb3_unicode_ci NOT NULL,
  `property_id` varchar(5) COLLATE utf8mb3_unicode_ci NOT NULL,
  `viewdate` date NOT NULL,
  `comment` text COLLATE utf8mb3_unicode_ci,
  PRIMARY KEY (`client_id`,`property_id`),
  KEY `property_id_viewing` (`property_id`),
  CONSTRAINT `client_FK_viewing` FOREIGN KEY (`client_id`) REFERENCES `client` (`client_id`),
  CONSTRAINT `property_id_viewing` FOREIGN KEY (`property_id`) REFERENCES `property4rent` (`property_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `viewing`
--

LOCK TABLES `viewing` WRITE;
/*!40000 ALTER TABLE `viewing` DISABLE KEYS */;
INSERT INTO `viewing` VALUES ('CR56','PA14','2016-05-24','too small'),('CR56','PG36','2016-04-28',NULL),('CR56','PG4','2016-05-26',NULL),('CR62','PA14','2016-05-14','no dinning room'),('CR76','PG4','2016-04-20','too remote');
/*!40000 ALTER TABLE `viewing` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2025-05-15  0:32:48
