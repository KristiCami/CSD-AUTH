<?php
session_start();

// Check if the user is logged in
if (!isset($_SESSION['loginame'])) {
    header("Location: ../index.php"); // Redirect to the login page if not logged in
    exit();
}

// Check the user's role
$role = $_SESSION['role'];

// Check if the user has the necessary role (e.g., 'Tutor') to delete announcements
if ($role !== 'Tutor') {
    header("Location: ../announcement.php"); // Redirect to the announcement page if not a Tutor
    exit();
}

// Include database connection
include "../db_Conn.php";

// Handle form submission
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    // Get the title from the form
    $titleToDelete = $_POST["titleToDelete"];

    // Use prepared statement to delete announcement
    $sql = "DELETE FROM announcements WHERE title=?";
    $stmt = mysqli_prepare($conn, $sql);

    if ($stmt === false) {
        die("Error in prepared statement: " . mysqli_error($conn));
    }

    // Bind parameters and execute the statement
    mysqli_stmt_bind_param($stmt, "s", $titleToDelete);
    mysqli_stmt_execute($stmt);

    // Check for success
    if (mysqli_stmt_affected_rows($stmt) > 0) {
        echo "Announcement deleted successfully.";
    } else {
        echo "Error deleting announcement. Announcement may not exist.";
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
    <title>Delete Announcement</title>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="../style.css">
</head>

<body>
    <?php include '../menu.php'; ?>

    <h2>Delete Announcement</h2>

    <form method="post" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>">
        <label for="titleToDelete">Enter Announcement Title to delete:</label>
        <input type="text" name="titleToDelete" required>

        <input type="submit" value="Delete Announcement">
    </form>
</body>

</html>
