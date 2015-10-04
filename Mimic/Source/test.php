<?php
	require_once('config.php');
	session_start();

	// Connect to server and select database.
	mysql_connect(DB_HOST, DB_USER, DB_PASSWORD)or die("cannot connect, error: ".mysql_error());
	mysql_select_db(DB_DATABASE)or die("cannot select DB, error: ".mysql_error());
	
	$sql="SELECT @RN:=@RN+1 as no, A.* FROM(SELECT * FROM scoreboard ORDER BY SCORE DESC) AS A, (SELECT @RN:=0) AS R";
	
	$query=mysql_query($sql);
	
	$result ="";
	$result .="<tr><th><img src=\"images/no.gif\"></th>";
        $result .="<th id><img src=\"images/name.gif\"></th>";
	$result .="<th id><img src=\"images/score.gif\"></th></tr>";
	
	while($rows=mysql_fetch_array($query)){
		$score = $rows['score'];
		if($score>=10000){
			$result.="<tr><td style='background-image: url(images/gold.png);
			background-repeat: no-repeat; background-size: contain; background-position: right;'>{$rows['no']}</td>";
		}else if($score>=8000){
			$result.="<tr><td style='background-image: url(images/silver.png);
			background-repeat: no-repeat; background-size: contain; background-position: right;'>{$rows['no']}</td>";
		}else if($score>=6000){
			$result.="<tr><td style='background-image: url(images/bronze.png);
			background-repeat: no-repeat; background-size: contain; background-position: right;'>{$rows['no']}</td>";
		}else{
			$result.="<tr><td>{$rows['no']}</td>";
		}
		$result.="<td>{$rows['name']}</td>";
		$result.="<td>{$rows['score']}</td></tr>";
	}
	
	echo $result;
	
	mysql_close();
?>

