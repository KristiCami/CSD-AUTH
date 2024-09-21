<?php
session_start();
include "db_Conn.php";

if (isset($_POST['uname']) && isset($_POST['psw'])) {

    $uname = $_POST['uname'];
    $pass = $_POST['psw'];


    $sql = "SELECT loginame, password,role FROM users WHERE loginame=?";
    $stmt = mysqli_prepare($conn, $sql);


    if ($stmt === false) {
        die("Σφάλμα στην προετοιμασία του ερωτήματος: " . mysqli_error($conn));
    }


    mysqli_stmt_bind_param($stmt, "s", $uname);
    mysqli_stmt_execute($stmt);
    $result = mysqli_stmt_get_result($stmt);


    if ($result) {
        $row = mysqli_fetch_assoc($result);

        if ($row && $pass == $row['password']) {

            $_SESSION['loginame'] = $row['loginame'];
            $_SESSION['role'] = $row['role'];

            header("Location: /3882partB/homepage.php");

            exit();
        } else {

            header("Location: /3882partB/index.html?error=Λανθασμένο όνομα χρήστη ή κωδικός πρόσβασης");
            exit();
        }
    } else {

        header("Location: /3882partB/index.html?error=Σφάλμα κατά την εκτέλεση του ερωτήματος");
        exit();
    }
} else {
    header("Location: /3882partB/index.html?error=Σφάλμα");
    exit();
}
