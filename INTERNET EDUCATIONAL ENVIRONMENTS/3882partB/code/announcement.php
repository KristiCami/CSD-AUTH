<?php
include "db_Conn.php";

// Fetch announcements from the database
$sql = "SELECT title, date, subject, announcementText FROM announcements ORDER BY date DESC";
$result = mysqli_query($conn, $sql);

if (!$result) {
    die("Error retrieving announcements: " . mysqli_error($conn));
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
    <title>Announcements</title>
    <link rel="stylesheet" href="style.css">
</head>

<body>
    <?php include 'menu.php'; ?>
    <?php
    // Loop through the announcements and display them
    while ($row = mysqli_fetch_assoc($result)) {
        echo "<div class='announcement'>";
        echo "<h2>{$row['title']}</h2>";
        echo "<p>Date: {$row['date']}</p>";
        echo "<p>Subject: {$row['subject']}</p>";
        echo "<p>{$row['announcementText']}</p>";
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
        echo "<li><a href='announcement/delete_announcement.php'>Delete Announcement</a></li>";
        echo "<li><a href='announcement/update_announcement.php'>Update Announcement</a></li>";
        echo "<li><a href='announcement/add_announcement.php'>Add Announcement</a></li>";
        echo "</ul>";
        echo "</div>";
    }
    ?>

</body>

</html>