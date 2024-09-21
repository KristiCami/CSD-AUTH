<?php
error_reporting(E_ALL);
ini_set('display_errors', 1);

use PHPMailer\PHPMailer\PHPMailer;

session_start();
include "db_Conn.php";
require 'vendor/autoload.php'; // Adjust the path to PHPMailerAutoload.php

// Check if the user is logged in
if (!isset($_SESSION['loginame'])) {
    header("Location: /index.php");
    exit();
}

// Function to send email to all users
function sendEmailToAllUsers($conn, $senderEmail, $title, $content)
{
    $sql = "SELECT DISTINCT loginame FROM users WHERE loginame IS NOT NULL";
    $result = mysqli_query($conn, $sql);

    if ($result) {
        while ($row = mysqli_fetch_assoc($result)) {
            $recipientEmail = $row['loginame'];

            // Use PHPMailer to send emails
            $mail = new PHPMailer;
            $mail->isSMTP(); // Set mailer to use SMTP
            $mail->Host = 'smtp.gmail.com'; // Specify your SMTP server
            $mail->Port = 465; // Specify the SMTP port
            $mail->SMTPAuth = true; // Enable SMTP authentication
            $mail->Username = 'tsami.christian@gmail.com'; // SMTP username
            $mail->Password = 'kjsh zhju ewon gbin'; // SMTP password
            $mail->SMTPSecure = 'ssl';
            $mail->setFrom($senderEmail);
            $mail->addAddress($recipientEmail);
            $mail->Subject = "Message: $title";
            $mail->Body = "$title\n\n$content";

            if (!$mail->send()) {
                echo 'Message could not be sent.';
                echo 'Mailer Error: ' . $mail->ErrorInfo;
            }
        }
    }
}

// Handle form submission
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    if (isset($_POST['sender_email']) && isset($_POST['title']) && isset($_POST['content'])) {
        $senderEmail = $_POST['sender_email'];
        $title = $_POST['title'];
        $content = $_POST['content'];

        // Send email to all users
        sendEmailToAllUsers($conn, $senderEmail, $title, $content);

        // Display success message
        echo "<p>Email sent successfully to all users.</p>";
    }
}

?>

<!DOCTYPE html>
<html lang="en">

<head>
    <title>Communication Page</title>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="style.css">
</head>

<body>
    <?php include 'menu.php'; ?>
    <h2>Communication Page</h2>

    <form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
        <label for="sender_email">Sender Email:</label>
        <input type="email" id="sender_email" name="sender_email" required>

        <label for="title">Title:</label>
        <input type="text" id="title" name="title" required>

        <label for="content">Main Content:</label>
        <textarea id="content" name="content" rows="4" required></textarea>

        <button type="submit">Send Email</button>
    </form>

    <p>
    Alternatively you can send an e-mail to the e-mail address below <a href="mailto:tutor@csd.auth.test.gr">tutor@csd.auth.test.gr</a>
    </p>

</body>

</html>