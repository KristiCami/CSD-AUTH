<?php
session_start();

// Check if the user is logged in
if (!isset($_SESSION['loginame'])) {
    header("Location: ../index.php"); // Redirect to the login page if not logged in
    exit();
}

// Check the user's role
$role = $_SESSION['role'];

// Check if the user has the necessary role (e.g., 'Tutor') to delete documents
if ($role !== 'Tutor') {
    header("Location: ../documents.php"); // Redirect to the documents page if not a Tutor
    exit();
}

// Include database connection
include "../db_Conn.php";

// Handle form submission
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    // Get the number from the form
    $numberToDelete = $_POST["numberToDelete"];

    // Use prepared statement to delete document
    $sql = "DELETE FROM documents WHERE number=?";
    $stmt = mysqli_prepare($conn, $sql);

    if ($stmt === false) {
        die("Error in prepared statement: " . mysqli_error($conn));
    }

    // Bind parameters and execute the statement
    mysqli_stmt_bind_param($stmt, "s", $numberToDelete);
    mysqli_stmt_execute($stmt);

    // Check for success
    if (mysqli_stmt_affected_rows($stmt) > 0) {
        echo "Document deleted successfully.";
    } else {
        echo "Error deleting document. Document may not exist.";
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
    <title>Delete Document</title>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="../style.css">
</head>

<body>
    <?php include '../menu.php'; ?>

    <h2>Delete Document</h2>

    <form method="post" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>">
        <label for="numberToDelete">Enter Document Number to delete:</label>
        <input type="text" name="numberToDelete" required>

        <input type="submit" value="Delete Document">
    </form>
</body>

</html>
