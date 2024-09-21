<?php
session_start();

// Check if the user is logged in
if (!isset($_SESSION['loginame'])) {
    header("Location: ../index.php"); // Redirect to the login page if not logged in
    exit();
}

// Check the user's role
$role = $_SESSION['role'];

// Check if the user has the required role (e.g., 'Tutor') to access this page
if ($role != 'Tutor') {
    header("Location: /3882partB/homepage.php"); // Redirect to the homepage if not authorized
    exit();
}

// Include database connection
include "../db_Conn.php";

// Handle form submission
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    // Get user details from the form
    $newName = $_POST["newName"];
    $newSurname = $_POST["newSurname"];
    $newUsername = $_POST["newUsername"];
    $newPassword = $_POST["newPassword"];
    $newRole = $_POST["newRole"];

    // Use prepared statement to insert new user
    $sql = "INSERT INTO users (name, surname, loginame, password, role) VALUES (?, ?, ?, ?, ?)";
    $stmt = mysqli_prepare($conn, $sql);

    if ($stmt === false) {
        die("Error in prepared statement: " . mysqli_error($conn));
    }

    // Bind parameters and execute the statement
    mysqli_stmt_bind_param($stmt, "sssss", $newName, $newSurname, $newUsername, $newPassword, $newRole);
    mysqli_stmt_execute($stmt);

    // Check for success
    if (mysqli_stmt_affected_rows($stmt) > 0) {
        echo "New user added successfully.";
    } else {
        echo "Error adding new user. User may already exist or there was a database error.";
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
    <title>Add User</title>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="../style.css">
</head>

<body>
    <?php include '../menu.php'; ?>

    <h2>Add User</h2>

    <form method="post" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>">
        <label for="newName">Name:</label>
        <input type="text" name="newName" required>

        <label for="newSurname">Surname:</label>
        <input type="text" name="newSurname" required>

        <label for="newUsername">Loginame:</label>
        <input type="text" name="newUsername" required>

        <label for="newPassword">Password:</label>
        <input type="password" name="newPassword" required>

        <label for="newRole">Role:</label>
        <input type="text" name="newRole" required>

        <input type="submit" value="Add User">
    </form>
</body>

</html>