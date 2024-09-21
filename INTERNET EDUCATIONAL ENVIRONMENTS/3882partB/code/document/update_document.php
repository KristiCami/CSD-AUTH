<?php
session_start();

// Check if the user is logged in
if (!isset($_SESSION['loginame'])) {
    header("Location: ../index.php"); // Redirect to the login page if not logged in
    exit();
}

// Check the user's role
$role = $_SESSION['role'];

// Check if the user has the necessary role (e.g., 'Tutor') to update documents
if ($role !== 'Tutor') {
    header("Location: /documents.php"); // Redirect to the documents page if not a Tutor
    exit();
}

// Include database connection
include "../db_Conn.php";

// Handle form submission
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    // Get the values from the form
    $numberToUpdate = $_POST["numberToUpdate"];
    $newTitle = $_POST["newTitle"];
    $newDescription = $_POST["newDescription"];
    $newPosition = $_POST["newPosition"];

    // Use prepared statement to update document
    $sql = "UPDATE documents SET title=?, description=?, position=? WHERE number=?";
    $stmt = mysqli_prepare($conn, $sql);

    if ($stmt === false) {
        die("Error in prepared statement: " . mysqli_error($conn));
    }

    // Bind parameters and execute the statement
    mysqli_stmt_bind_param($stmt, "ssss", $newTitle, $newDescription, $newPosition, $numberToUpdate);
    mysqli_stmt_execute($stmt);

    // Check for success
    if (mysqli_stmt_affected_rows($stmt) > 0) {
        echo "Document updated successfully.";
    } else {
        echo "Error updating document. Document may not exist.";
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
    <title>Update Document</title>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="../style.css">
</head>

<body>
    <?php include '../menu.php'; ?>

    <h2>Update Document</h2>

    <form method="post" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>">
        <label for="numberToUpdate">Enter Document Number to update:</label>
        <input type="text" name="numberToUpdate" required>

        <label for="newTitle">New Document Title:</label>
        <input type="text" name="newTitle" required>

        <label for="newDescription">New Document Description:</label>
        <textarea name="newDescription" required></textarea>

        <label for="newPosition">New Document Position:</label>
        <input type="text" name="newPosition" required>

        <input type="submit" value="Update Document">
    </form>
</body>

</html>
