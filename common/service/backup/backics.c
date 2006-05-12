/* (c) 2003 by Marcin Wiacek */

#include <string.h>
#include <ctype.h>

#include "../../phone/nokia/nfunc.h"
#include "../../phone/nokia/dct3/n7110.h"
#include "../../misc/coding/coding.h"
#include "../gsmlogo.h"
#include "../gsmmisc.h"
#include "backics.h"

#ifdef GSM_ENABLE_BACKUP

GSM_Error SaveICS(char *FileName, GSM_Backup *backup)
{
	int 		i, Length = 0;
	unsigned char 	Buffer[1000];
	FILE 		*file;

	file = fopen(FileName, "wb");
	if (file == NULL) return ERR_CANTOPENFILE;

	Length=sprintf(Buffer, "BEGIN:VCALENDAR%c%c",13,10);
	Length+=sprintf(Buffer+Length, "VERSION:1.0%c%c",13,10);
	fwrite(Buffer,1,Length,file);

	i=0;
	while (backup->Calendar[i]!=NULL) {
		sprintf(Buffer, "%c%c",13,10);
		fwrite(Buffer,1,2,file);
		Length = 0;
		GSM_EncodeVCALENDAR(Buffer,&Length,backup->Calendar[i],false,Mozilla_VCalendar);
		fwrite(Buffer,1,Length,file);
		i++;
	}
	i=0;
	while (backup->ToDo[i]!=NULL) {
		sprintf(Buffer, "%c%c",13,10);
		fwrite(Buffer,1,2,file);
		Length = 0;
		GSM_EncodeVTODO(Buffer,&Length,backup->ToDo[i],false,Mozilla_VToDo);
		fwrite(Buffer,1,Length,file);
		i++;
	}

	Length=sprintf(Buffer, "%c%cEND:VCALENDAR%c%c",13,10,13,10);
	fwrite(Buffer,1,Length,file);

	fclose(file);
	return ERR_NONE;
}

GSM_Error LoadICS(char *FileName, GSM_Backup *backup)
{
	GSM_File 		File;
	GSM_Error		error;

	File.Buffer = NULL;
	error = GSM_ReadFile(FileName, &File);
	if (error != ERR_NONE) return error;

	return ERR_NONE;
}

#endif

/* How should editor hadle tabs in this file? Add editor commands here.
 * vim: noexpandtab sw=8 ts=8 sts=8:
 */
