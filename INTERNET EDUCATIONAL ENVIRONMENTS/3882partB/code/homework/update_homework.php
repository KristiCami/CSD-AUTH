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
    $titleToUpdate = $_POST["titleToUpdate"];
    $dateToUpdate = $_POST["dateToUpdate"];
    $newSubject = $_POST["newSubject"];
    $newHomeworkText = $_POST["newHomeworkText"];
    $newDeliveryText = $_POST["newDeliveryText"];

    // Use prepared statement to update homework entry
    $sql = "UPDATE homework SET subject=?, homeworkText=?, deli_Text=? WHERE title=? AND date=?";
    $stmt = mysqli_prepare($conn, $sql);

    if ($stmt === false) {
        die("Error in prepared statement: " . mysqli_error($conn));
    }

    // Bind parameters and execute the statement
    mysqli_stmt_bind_param($stmt, "sssss", $newSubject, $newHomeworkText, $newDeliveryText, $titleToUpdate, $dateToUpdate);
    mysqli_stmt_execute($stmt);

    // Check for success
    if (mysqli_stmt_affected_rows($stmt) > 0) {
        echo "Homework updated successfully.";
    } else {
        echo "Error updating homework. Homework may not exist.";
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
    <title>Update Homework</title>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="../style.css">
</head>

<body>
    <?php include '../menu.php'; ?>

    <h2>Update Homework</h2>

    <form method="post" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>">
        <label for="titleToUpdate">Enter Homework Title to update:</label>
        <input type="text" name="titleToUpdate" required>

        <label for="dateToUpdate">Enter Homework Date to update:</label>
        <input type="text" name="dateToUpdate" required>

        <label for="newSubject">New Subject:</label>
        <input type="text" name="newSubject" required>

        <label for="newHomeworkText">New Homework Text:</label>
        <textarea name="newHomeworkText" required></textarea>

        <label for="newDeliveryText">New Delivery Text:</label>
        <textarea name="newDeliveryText" required></textarea>

        <input type="submit" value="Update Homework">
    </form>
</body>

</html>
