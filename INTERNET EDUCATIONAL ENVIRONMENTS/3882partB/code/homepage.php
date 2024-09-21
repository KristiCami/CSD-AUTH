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
    <title>My page</title>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet"  href="style.css">
</head>

<body>
    <?php include 'menu.php'; ?>
    <h2>Welcome</h2>
    <p>
        Lorem ipsum dolor sit amet consectetur, adipisicing elit. Beatae ratione eaque eligendi ipsa sit commodi asperiores porro odit eius dolorum, maxime, quia corporis adipisci sunt nobis nostrum perferendis, inventore culpa.
        Dolorem laudantium, aperiam reiciendis aliquid, explicabo reprehenderit temporibus blanditiis dicta possimus amet repellendus deleniti adipisci voluptates, repellat incidunt. Nesciunt quae esse eaque fuga ducimus quasi. Nemo sed aliquam quasi deserunt.
        Obcaecati maiores tempora sapiente voluptates debitis accusantium error distinctio inventore ipsa aut perspiciatis sequi ad nisi voluptatibus labore magnam, saepe sunt laboriosam commodi? Asperiores architecto quisquam nihil suscipit, magnam quibusdam.
        Iure aspernatur officia natus ex blanditiis dolorem accusamus quidem, nisi perferendis sint eveniet nesciunt nam error, magni illo laborum a magnam earum velit temporibus maxime autem! Molestiae distinctio id voluptate.
        Ea, harum a fugit magni quibusdam voluptas, explicabo tenetur suscipit atque hic doloribus officiis facilis rerum totam maxime optio qui iure quas, incidunt voluptatum aperiam! Beatae ab quasi reiciendis magnam?
        Nesciunt, aperiam doloribus ullam possimus laborum distinctio sequi numquam praesentium consequatur architecto cupiditate, corrupti repudiandae at ducimus pariatur nulla fuga harum ut in id animi, quidem inventore mollitia quaerat. Voluptatem.
    </p>
    <div class="centered-image">
    <img src="images/success_icon.png" alt="Success icon">
    </div>
    <?php
    // Display additional options for Tutors
    if ($role == 'Tutor') {
        echo "<div>";
        echo "<h3>Tutor Options:</h3>";
        echo "<ul>";
        echo "<li><a href='users/delete_user.php'>Delete Users</a></li>";
        echo "<li><a href='users/update_user.php'>Update Users</a></li>";
        echo "<li><a href='users/add_user.php'>Add User</a></li>";
        echo "</ul>";
        echo "</div>";
    }
    ?>
</body>

</html>