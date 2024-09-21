<?php
session_start();

// Check if the user is logged in
if (!isset($_SESSION['loginame'])) {
    header("Location: ../index.php"); // Redirect to the login page if not logged in
    exit();
}

// Check the user's role
$role = $_SESSION['role'];

// Check if the user has the necessary role (e.g., 'Tutor') to add documents
if ($role !== 'Tutor') {
    header("Location: ../documents.php"); // Redirect to the documents page if not a Tutor
    exit();
}

// Include database connection
include "../db_Conn.php";

// Handle form submission
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    // Get the values from the form
    $number = $_POST["number"];
    $title = $_POST["title"];
    $description = $_POST["description"];
    $position = $_POST["position"];

    // Use prepared statement to insert new document
    $sql = "INSERT INTO documents (number, title, description, position) VALUES (?, ?, ?, ?)";
    $stmt = mysqli_prepare($conn, $sql);

    if ($stmt === false) {
        die("Error in prepared statement: " . mysqli_error($conn));
    }

    // Bind parameters and execute the statement
    mysqli_stmt_bind_param($stmt, "ssss", $number, $title, $description, $position);
    mysqli_stmt_execute($stmt);

    // Check for success
    if (mysqli_stmt_affected_rows($stmt) > 0) {
        echo "Document added successfully.";
    } else {
        echo "Error adding document. Check if the number already exists.";
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
    <title>Add Document</title>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="../style.css">
</head>

<body>
    <?php include '../menu.php'; ?>

    <h2>Add Document</h2>

    <form method="post" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>">
        <label for="number">Document Number:</label>
        <input type="text" name="number" required>

        <label for="title">Document Title:</label>
        <input type="text" name="title" required>

        <label for="description">Document Description:</label>
        <textarea name="description" required></textarea>

        <label for="position">Document Position:</label>
        <input type="text" name="position" required>

        <input type="submit" value="Add Document">
    </form>
</body>

</html>
