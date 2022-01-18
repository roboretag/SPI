//Funcion que crea la tarea -->xTaskCreate
void spiInit(void)
{
	xTaskCreate(	spiTask,		/* Pointer to the function that implements the task. */
					"spiTask",	/* Text name for the task.  This is to facilitate debugging only. */
					200,				/* Stack depth in words. */
					NULL,				/* We are not using the task parameter. */
					2,					/* This task will run at priority 1. */
					NULL );				/* We are not using the task handle. */
}


void spiTask (void *argument)
{
	//char data_out[] = "Hola";
	uint8_t spiTransmitBuffer[5];
	uint8_t spi_ReceiveBuffer[1];
	//uint8_t spi_ReceiveBuffer[spiTransmitBuffer];
	//uint8_t spiTransferSize = 3;

	while(1)
	{


		//Transmito Command + Addres + Data
	    spiTransmitBuffer[0] = (uint8_t) ((COMMAND_READ << 4) + ((ADDRESS >> 8) & 0xF));
	    spiTransmitBuffer[1] = (uint8_t) (ADDRESS & 0xFF);

	    //comande reset -->MISO FF FF FF ...
	    spiTransmitBuffer[2] = 0x48;
	    spiTransmitBuffer[3] = 0x6F;
	    spiTransmitBuffer[4] = 0x6C;
	    spiTransmitBuffer[5] = 0x61;

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);//0
		HAL_SPI_Transmit(&hspi3, spiTransmitBuffer,2, HAL_MAX_DELAY); //Envio
		HAL_SPI_Receive(&hspi3, spi_ReceiveBuffer,1, HAL_MAX_DELAY);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);



		vTaskDelay(pdMS_TO_TICKS(1000));


	}
}
