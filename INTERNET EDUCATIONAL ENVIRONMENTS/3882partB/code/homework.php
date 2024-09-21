<?php
include "db_Conn.php";

// Fetch homework from the database
$sql = "SELECT title, subject, homeworkText, deli_Text, date FROM homework ORDER BY date DESC";
$result = mysqli_query($conn, $sql);

if (!$result) {
    die("Error retrieving homework: " . mysqli_error($conn));
}

?>
<?php
session_start();

// Check if the user is logged in
if (!isset($_SESSION['loginame'])) {
    header("Location: /index.php"); // Redirect to the login page if not logged in
    exit();
}

// Check the user's role
$role = $_SESSION['role'];

?>
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Homework</title>
    <link rel="stylesheet" href="style.css">
</head>

<body>
        <?php include 'menu.php'; ?>

        <?php
        // Loop through the homework and display them
        while ($row = mysqli_fetch_assoc($result)) {
            echo "<div class='homework'>";
            echo "<h2>{$row['title']}</h2>";
            echo "<p>Subject: {$row['subject']}</p>";
            echo "<p>Homework Text: {$row['homeworkText']}</p>";
            echo "<p>Delivery Text: {$row['deli_Text']}</p>";
            echo "<p>Date: {$row['date']}</p>";
            echo "</div>";
        }

        // Close the result set
        mysqli_free_result($result);

        // Close the database connection
        mysqli_close($conn);
        ?>

        <?php
        // Display additional options for Tutors
        if ($role == 'Tutor') {
            echo "<div>";
            echo "<h3>Tutor Options:</h3>";
            echo "<ul>";
            echo "<li><a href='homework/delete_homework.php'>Delete Homework</a></li>";
            echo "<li><a href='homework/update_homework.php'>Update Homework</a></li>";
            echo "<li><a href='homework/add_homework.php'>Add Homework</a></li>";
            echo "</ul>";
            echo "</div>";
        }
        ?>
</body>

</html>