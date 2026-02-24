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
