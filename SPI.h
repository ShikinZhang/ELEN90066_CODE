
#define WRITE 	0x02
#define READ 	0x03

void SPI_Master_Init();
void SPI_MasterTransmit(char cData);
void SPI_SlaveInit(void);
char SPI_SlaveReceive(void);

void FRAM_Pre_Write();
void SPI_SR_Write();
void SPI_Sim_Tx_8bit(byte data);
void FRAM_Write(byte AddrH, byte AddrL, byte Data);
byte FRAM_Read(byte AddrH, byte AddrL);
