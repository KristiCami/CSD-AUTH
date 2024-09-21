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
    header("Location: ../homepage.php"); // Redirect to the homepage if not authorized
    exit();
}

// Include database connection
include "../db_Conn.php";

// Handle form submission
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    // Get user details from the form
    $usernameToUpdate = $_POST["usernameToUpdate"];
    $newPassword = $_POST["newPassword"];
    $newRole = $_POST["newRole"];

    // Use prepared statement to update user information
    $sql = "UPDATE users SET password=?, role=? WHERE loginame=?";
    $stmt = mysqli_prepare($conn, $sql);

    if ($stmt === false) {
        die("Error in prepared statement: " . mysqli_error($conn));
    }

    // Bind parameters and execute the statement
    mysqli_stmt_bind_param($stmt, "sss", $newPassword, $newRole, $usernameToUpdate);
    mysqli_stmt_execute($stmt);

    // Check for success
    if (mysqli_stmt_affected_rows($stmt) > 0) {
        echo "User information updated successfully.";
    } else {
        echo "Error updating user information. User may not exist.";
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
    <title>Edit Users</title>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="../style.css">
</head>

<body>
    <?php include '../menu.php'; ?>

    <h2>Edit Users</h2>

    <form method="post" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>">
        <label for="usernameToUpdate">Enter Username (loginame) to edit:</label>
        <input type="text" name="usernameToUpdate" required>

        <label for="newPassword">New Password:</label>
        <input type="password" name="newPassword" required>

        <label for="newRole">New Role:</label>
        <input type="text" name="newRole" required>

        <input type="submit" value="Update User">
    </form>
</body>

</html>