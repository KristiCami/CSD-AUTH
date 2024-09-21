<?php
session_start();

// Check if the user is logged in
if (!isset($_SESSION['loginame'])) {
    header("Location: ../index.php"); // Redirect to the login page if not logged in
    exit();
}


// Include database connection
include "../db_Conn.php";

// Handle form submission
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    // Get the title and date from the form
    $titleToDelete = $_POST["titleToDelete"];
    $dateToDelete = $_POST["dateToDelete"];

    // Use prepared statement to delete homework entry
    $sql = "DELETE FROM homework WHERE title=? AND date=?";
    $stmt = mysqli_prepare($conn, $sql);

    if ($stmt === false) {
        die("Error in prepared statement: " . mysqli_error($conn));
    }

    // Bind parameters and execute the statement
    mysqli_stmt_bind_param($stmt, "ss", $titleToDelete, $dateToDelete);
    mysqli_stmt_execute($stmt);

    // Check for success
    if (mysqli_stmt_affected_rows($stmt) > 0) {
        echo "Homework deleted successfully.";
    } else {
        echo "Error deleting homework. Homework may not exist.";
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
    <title>Delete Homework</title>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="../style.css">
</head>

<body>
    <?php include '../menu.php'; ?>

    <h2>Delete Homework</h2>

    <form method="post" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>">
        <label for="titleToDelete">Enter Homework Title to delete:</label>
        <input type="text" name="titleToDelete" required>

        <label for="dateToDelete">Enter Homework Date to delete:</label>
        <input type="text" name="dateToDelete" required>

        <input type="submit" value="Delete Homework">
    </form>
</body>

</html>
