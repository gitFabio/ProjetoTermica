
<?php

	$hDesp = $_POST["hora"];
	$mDesp = $_POST["minutos"];
	$temperatura = $_POST["temp"];
	$hAtual = date("h");
	$mAtual = date("i");
	$sAtual = date("s");


	echo nl2br("Hora atual " . $hAtual . "h " . $mAtual . "m " . $sAtual ."s");

	echo nl2br("\n\n=====================================");
	echo nl2br("\nHora programada para despertar e temperatura");
	echo nl2br("\nHora [". $hDesp . "]\n Minuto [". $mDesp . "]");
	echo nl2br("\nTemperatura " . $temperatura . "C");

	$port = fopen("/dev/ttyACM0", "w");


	echo nl2br("\n\n===============");
	echo nl2br("\n\tTeste do arduino");

	
	if(fwrite($port, "a")){
		echo nl2br("\nLigou sucesso");
	}else{
		echo nl2br("\nNao ligou");
	}

?>