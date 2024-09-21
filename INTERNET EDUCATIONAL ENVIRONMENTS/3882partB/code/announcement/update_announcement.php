<?php
session_start();

// Check if the user is logged in
if (!isset($_SESSION['loginame'])) {
    header("Location: ../index.php"); // Redirect to the login page if not logged in
    exit();
}

// Check the user's role
$role = $_SESSION['role'];

// Check if the user has the necessary role (e.g., 'Tutor') to update announcements
if ($role !== 'Tutor') {
    header("Location: ../announcement.php"); // Redirect to the announcement page if not a Tutor
    exit();
}

// Include database connection
include "../db_Conn.php";

// Handle form submission
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    // Get the values from the form
    $titleToUpdate = $_POST["titleToUpdate"];
    $newDate = $_POST["newDate"];
    $newSubject = $_POST["newSubject"];
    $newAnnouncementText = $_POST["newAnnouncementText"];

    // Use prepared statement to update announcement
    $sql = "UPDATE announcements SET date=?, subject=?, announcementText=? WHERE title=?";
    $stmt = mysqli_prepare($conn, $sql);

    if ($stmt === false) {
        die("Error in prepared statement: " . mysqli_error($conn));
    }

    // Bind parameters and execute the statement
    mysqli_stmt_bind_param($stmt, "ssss", $newDate, $newSubject, $newAnnouncementText, $titleToUpdate);
    mysqli_stmt_execute($stmt);

    // Check for success
    if (mysqli_stmt_affected_rows($stmt) > 0) {
        echo "Announcement updated successfully.";
    } else {
        echo "Error updating announcement. Announcement may not exist.";
    }

    // Close the statement
    mysqli_stmt_close($stmt);
}

// Close the database connection
mysqli_close($conn);
?>

<!DOCTYPE html>
<html lang="en">

<head>
    <title>Update Announcement</title>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="../style.css">
</head>

<body>
    <?php include '../menu.php'; ?>

    <h2>Update Announcement</h2>

    <form method="post" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>">
        <label for="titleToUpdate">Enter Announcement Title to update:</label>
        <input type="text" name="titleToUpdate" required>

        <label for="newDate">New Date:</label>
        <input type="text" name="newDate" required>

        <label for="newSubject">New Subject:</label>
        <input type="text" name="newSubject" required>

        <label for="newAnnouncementText">New Announcement Text:</label>
        <textarea name="newAnnouncementText" required></textarea>

        <input type="submit" value="Update Announcement">
    </form>
</body>

</html>
