<?php
include "db_Conn.php";

// Fetch documents from the database
$sql = "SELECT number, title, description, position FROM documents ORDER BY position ASC";
$result = mysqli_query($conn, $sql);

if (!$result) {
    die("Error retrieving documents: " . mysqli_error($conn));
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
    <title>Documents</title>
    <link rel="stylesheet" href="style.css">
</head>

<body>
    <?php include 'menu.php'; ?>
    <?php
    // Loop through the documents and display them
    while ($row = mysqli_fetch_assoc($result)) {
        echo "<div class='document'>";
        echo "<p>Number: {$row['number']}</p>";
        echo "<h2>{$row['title']}</h2>";
        echo "<p>Description: {$row['description']}</p>";
        echo "<p>Position: {$row['position']}</p>";
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
        echo "<li><a href='document/delete_document.php'>Delete Document</a></li>";
        echo "<li><a href='document/update_document.php'>Update Document</a></li>";
        echo "<li><a href='document/add_document.php'>Add Document</a></li>";
        echo "</ul>";
        echo "</div>";
    }
    ?>

</body>

</html>