CREATE TABLE
    IF NOT EXISTS `hku_base`.`block` (
        `id` INT UNSIGNED NOT NULL AUTO_INCREMENT,
        `category` VARCHAR(100) NOT NULL,
        `content` LONGTEXT,
        PRIMARY KEY (`id`),
        INDEX `ix_block` (`category`)
    ) COLLATE = 'utf8_general_ci' ENGINE = InnoDB;

UPDATE `hku_base`.`version` set `version` = 10;