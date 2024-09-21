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
    // Get the values from the form
    $title = $_POST["title"];
    $subject = $_POST["subject"];
    $homeworkText = $_POST["homeworkText"];
    $deli_Text = $_POST["deli_Text"];
    $date = $_POST["date"];

    // Use prepared statement to insert new homework
    $sql = "INSERT INTO homework (title, subject, homeworkText, deli_Text, date) VALUES (?, ?, ?, ?, ?)";
    $stmt = mysqli_prepare($conn, $sql);

    if ($stmt === false) {
        die("Error in prepared statement: " . mysqli_error($conn));
    }

    // Bind parameters and execute the statement
    mysqli_stmt_bind_param($stmt, "sssss", $title, $subject, $homeworkText, $deli_Text, $date);
    mysqli_stmt_execute($stmt);

    // Check for success
    if (mysqli_stmt_affected_rows($stmt) > 0) {
        echo "Homework added successfully.";
    } else {
        echo "Error adding homework.";
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
    <title>Add Homework</title>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="../style.css">
</head>

<body>
    <?php include '../menu.php'; ?>

    <h2>Add Homework</h2>

    <form method="post" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>">
        <label for="title">Homework Title:</label>
        <input type="text" name="title" required>

        <label for="subject">Subject:</label>
        <input type="text" name="subject" required>

        <label for="homeworkText">Homework Text:</label>
        <textarea name="homeworkText" required></textarea>

        <label for="deli_Text">Delivery Text:</label>
        <input type="text" name="deli_Text" required>

        <label for="date">Date:</label>
        <input type="date" name="date" required>

        <input type="submit" value="Add Homework">
    </form>
</body>

</html>
