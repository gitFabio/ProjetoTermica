
<?php
/*
	$hDesp = $_POST["hora"];
	$mDesp = $_POST["minutos"];
	$temperatura = $_POST["temp"];*/
	$hDesp = "20";
	$mDesp = "30";
	$temperatura = "90";
	$hAtual = date("H");
	$mAtual = date("i");
	$sAtual = date("s");

	$enviar = "#".$hAtual."#"."%".$mAtual."%"."*".$sAtual."*"."@".$temperatura."@"."!".$hDesp."!"."=".$mDesp."=";

	echo nl2br("Hora atual " . $hAtual . "h " . $mAtual . "m " . $sAtual ."s");

	echo nl2br("\n\n=====================================");
	echo nl2br("\nHora programada para despertar e temperatura");
	echo nl2br("\nHora [". $hDesp . "]\n Minuto [". $mDesp . "]");
	echo nl2br("\nTemperatura " . $temperatura . "C");

try{
	$port = '/dev/ttyUSB0';
	$con = fopen($port, 'r+');

	echo nl2br("\n\n===============");
	echo nl2br("\n\tTeste do arduino");

	fwrite($con, $enviar);
	echo nl2br("\nLigou sucesso\n");

	fclose($con);
	
}catch(Exeption $e){
	echo nl2br("\nNao ligou\n");
	echo nl2br("Erro ", $e.getMessage);
}


?>