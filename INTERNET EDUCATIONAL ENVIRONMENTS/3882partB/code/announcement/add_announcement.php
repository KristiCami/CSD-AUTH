<?php
session_start();

// Check if the user is logged in
if (!isset($_SESSION['loginame'])) {
    header("Location: ../index.php"); // Redirect to the login page if not logged in
    exit();
}

// Check the user's role
$role = $_SESSION['role'];

// Check if the user has the necessary role (e.g., 'Tutor') to add announcements
if ($role !== 'Tutor') {
    header("Location: ../announcement.php"); // Redirect to the announcement page if not a Tutor
    exit();
}

// Include database connection
include "../db_Conn.php";

// Handle form submission
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    // Get the values from the form
    $title = $_POST["title"];
    $date = $_POST["date"];
    $subject = $_POST["subject"];
    $announcementText = $_POST["announcementText"];

    // Use prepared statement to insert new announcement
    $sql = "INSERT INTO announcements (title, date, subject, announcementText) VALUES (?, ?, ?, ?)";
    $stmt = mysqli_prepare($conn, $sql);

    if ($stmt === false) {
        die("Error in prepared statement: " . mysqli_error($conn));
    }

    // Bind parameters and execute the statement
    mysqli_stmt_bind_param($stmt, "ssss", $title, $date, $subject, $announcementText);
    mysqli_stmt_execute($stmt);

    // Check for success
    if (mysqli_stmt_affected_rows($stmt) > 0) {
        echo "Announcement added successfully.";
    } else {
        echo "Error adding announcement. Check if the title already exists.";
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
    <title>Add Announcement</title>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="../style.css">
</head>

<body>
    <?php include '../menu.php'; ?>

    <h2>Add Announcement</h2>

    <form method="post" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>">
        <label for="title">Announcement Title:</label>
        <input type="text" name="title" required>

        <label for="date">Date:</label>
        <input type="text" name="date" required>

        <label for="subject">Subject:</label>
        <input type="text" name="subject" required>

        <label for="announcementText">Announcement Text:</label>
        <textarea name="announcementText" required></textarea>

        <input type="submit" value="Add Announcement">
    </form>
</body>

</html>
