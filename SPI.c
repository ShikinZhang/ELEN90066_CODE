#include "game_console.h"
#include "SPI.h"

void SPI_Master_Init()
{
	
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

void SPI_MasterTransmit(char cData)
{
	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)));
}

void SPI_SlaveInit(void)
{
	/* Set MISO output, all others input */
	//DDR_SPI = (1<<DD_MISO);
	/* Enable SPI */
	SPCR = (1<<SPE);
}
char SPI_SlaveReceive(void)
{
	/* Wait for reception complete */
	while(!(SPSR & (1<<SPIF)));
	/* Return data register */
	return SPDR;
}

void FRAM_Pre_Write()
{
	byte WREN;
	WREN = 0X06;

	CS_INIT(LOW); 
	SPI_MasterTransmit(WREN);
	CS_INIT(HIGH);

}

void SPI_SR_Write()
{
	byte data_mask;
	byte i;

	SCK_LOW;
	CS_SELECT;

	data_mask = 0x80;

	for (i = 0; i < 8; i++)
	{	
		if((data_mask & 0x05) == data_mask )
			MOSI_HIGH;
		else
			MOSI_LOW;
		SCK_LOW;
		_delay_us(100);
		SCK_HIGH;
		_delay_us(100);
		data_mask = data_mask >> 1;
	}

	data_mask = 0x80;

	for (i = 0; i < 8; i++)
	{	
		if((data_mask & 0x02) == data_mask )
			MOSI_HIGH;
		else
			MOSI_LOW;
		SCK_LOW;
		_delay_us(100);
		SCK_HIGH;
		_delay_us(100);
		data_mask = data_mask >> 1;
	}

	CS_DESELECT;
	SCK_LOW;
}

void SPI_Sim_Tx_8bit(byte data)
{
	byte data_mask;
	byte i;

	SCK_LOW;
	CS_SELECT;
	data_mask = 0x80;

	for (i = 0; i < 8; i++)
	{	
		if((data_mask & data) == data_mask )
			MOSI_HIGH;
		else
			MOSI_LOW;
		SCK_LOW;
		_delay_us(100);
		SCK_HIGH;
		_delay_us(100);
		data_mask = data_mask >> 1;
	}
	CS_DESELECT;
	SCK_LOW;
}


void FRAM_Write (byte AddrH, byte AddrL, byte Data)
{
	// byte Opcode;
	// Opcode = WRITE;
	// FRAM_Pre_Write();
	// CS_INIT(LOW); 
	// SPI_MasterTransmit(Opcode);
	// SPI_MasterTransmit(AddrH);
	// SPI_MasterTransmit(AddrL);
	// SPI_MasterTransmit(Data);
	// CS_INIT(HIGH); 
	byte data_mask;
	byte i;

	SCK_LOW;
	CS_SELECT;

	data_mask = 0x80;

	for (i = 0; i < 8; i++)
	{	
		if((data_mask & 0x02) == data_mask )
			MOSI_HIGH;
		else
			MOSI_LOW;
		SCK_LOW;
		_delay_us(100);
		SCK_HIGH;
		_delay_us(100);
		data_mask = data_mask >> 1;
	}

	data_mask = 0x80;

	for (i = 0; i < 8; i++)
	{	
		if((data_mask & AddrH) == data_mask )
			MOSI_HIGH;
		else
			MOSI_LOW;
		SCK_LOW;
		_delay_us(100);
		SCK_HIGH;
		_delay_us(100);
		data_mask = data_mask >> 1;
	}

	data_mask = 0x80;

	for (i = 0; i < 8; i++)
	{	
		if((data_mask & AddrL) == data_mask )
			MOSI_HIGH;
		else
			MOSI_LOW;
		SCK_LOW;
		_delay_us(100);
		SCK_HIGH;
		_delay_us(100);
		data_mask = data_mask >> 1;
	}

	data_mask = 0x80;

	for (i = 0; i < 8; i++)
	{	
		if((data_mask & Data) == data_mask )
			MOSI_HIGH;
		else
			MOSI_LOW;
		SCK_LOW;
		_delay_us(100);
		SCK_HIGH;
		_delay_us(100);
		data_mask = data_mask >> 1;
	}


	CS_DESELECT;
	SCK_LOW;

}

byte FRAM_Read(byte AddrH, byte AddrL)
{
	// byte Opcode;
	// byte Data;
	// Opcode = READ;

	// CS_INIT(LOW); 
	// SPI_MasterTransmit(Opcode);
	// SPI_MasterTransmit(AddrH);
	// SPI_MasterTransmit(AddrL);
	// while(!(SPSR & (1<<SPIF)));
	// Data = SPDR;
	// CS_INIT(HIGH); 

	// return Data;


	byte data_mask;
	byte i;
	byte data;

	SCK_LOW;
	CS_SELECT;

	data = 0;
	data_mask = 0x80;

	for (i = 0; i < 8; i++)
	{	
		if((data_mask & 0x03) == data_mask )
			MOSI_HIGH;
		else
			MOSI_LOW;
		SCK_LOW;
		_delay_us(100);
		SCK_HIGH;
		_delay_us(100);
		data_mask = data_mask >> 1;
	}

	data_mask = 0x80;

	for (i = 0; i < 8; i++)
	{	
		if((data_mask & AddrH) == data_mask )
			MOSI_HIGH;
		else
			MOSI_LOW;
		SCK_LOW;
		_delay_us(100);
		SCK_HIGH;
		_delay_us(100);
		data_mask = data_mask >> 1;
	}

	data_mask = 0x80;

	for (i = 0; i < 8; i++)
	{	
		if((data_mask & AddrL) == data_mask )
			MOSI_HIGH;
		else
			MOSI_LOW;
		SCK_LOW;
		_delay_us(100);
		SCK_HIGH;
		_delay_us(100);
		data_mask = data_mask >> 1;
	}

	data_mask = 0x80;

	for (i = 0; i < 8; i++)
	{	
		SCK_LOW;
		_delay_us(100);
		SCK_HIGH;

		if(MISO_READ)
			data = (data<<1) + 1;
		else
			data = data<<1;

		_delay_us(100);
	}


	CS_DESELECT;
	SCK_LOW;

	return data;
}


