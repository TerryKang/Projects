<?php
require_once('config.php');

// Connect to server and select database.
mysql_connect(DB_HOST, DB_USER, DB_PASSWORD)or die("cannot connect");
mysql_select_db(DB_DATABASE)or die("cannot select DB");
$tbl_name="scoreboard"; // Table name

// Get value of id that sent from hidden field
$score=$_POST['score'];

// get values that sent from form
$name=$_POST['name'];

$sql="INSERT INTO scoreboard ('name', 'score')VALUES('$name', '$score')";
$result=mysql_query($sql);

if($result){
	echo $result;
}
else {
	echo "ERROR".mysql_error();
}

mysql_close();
?>

