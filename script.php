<?php



if ( isset( $_GET['newCodeAdded'] ) )
{
	/* Open the file */
	$myfile_2 = fopen("codeStatus.txt","w");


	if ( $_GET['newCodeAdded'] == 'True')
	{
		fwrite($myfile_2,'1');
		
	}
	elseif ( $_GET['newCodeAdded'] == 'False')
	{
		fwrite($myfile_2,'0');
		header ("Location: test.php?config=doneBurn" );
		
	}
	/* Close the file */
	fclose($myfile_2);
}

if ( isset( $_GET['getnewCodeS'] ) )
{
	/* Open the file */
	$myfile_2 = fopen("codeStatus.txt","r");
	$getnewCodeS =  fgets($myfile_2);

	if ($getnewCodeS  == '1')
	{
		echo "True";
		
	}
	elseif ($getnewCodeS  == '0')
	{
		echo "False";
		
	}
	/* Close the file */
	fclose($myfile_2);
}


?>