<?php
$host = "webpagesdb.it.auth.gr:3306";
$dbUser = "tsamikristi";
$dbPassword = "admin123";
$dbName = "loginpage";
$conn = mysqli_connect($host, $dbUser, $dbPassword, $dbName);
if (!$conn) {
    die("something went wrong");
}


