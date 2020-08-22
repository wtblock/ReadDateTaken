/////////////////////////////////////////////////////////////////////////////
// Copyright © by W. T. Block, all rights reserved
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "ReadDateTaken.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object
CWinApp theApp;

/////////////////////////////////////////////////////////////////////////////
// Save the data inside pImage to the given lpszPathName
bool Save( LPCTSTR lpszPathName, Gdiplus::Image* pImage )
{
	USES_CONVERSION;

	CString csExt = GetExtension( lpszPathName );

	// save and overwrite the selected image file with current page
	int iValue =
		EncoderValue::EncoderValueVersionGif89 |
		EncoderValue::EncoderValueCompressionLZW |
		EncoderValue::EncoderValueFlush;

	EncoderParameters param;
	param.Count = 1;
	param.Parameter[ 0 ].Guid = EncoderSaveFlag;
	param.Parameter[ 0 ].Value = &iValue;
	param.Parameter[ 0 ].Type = EncoderParameterValueTypeLong;
	param.Parameter[ 0 ].NumberOfValues = 1;

	// writing to the same file will fail, so save to a corrected folder
	// below the image being corrected
	const CString csCorrected = GetCorrectedFolder();
	const CString csFolder = GetFolder( lpszPathName ) + csCorrected;
	if ( !::PathFileExists( csFolder ) )
	{
		if ( !CreatePath( csFolder ) )
		{
			return false;
		}
	}

	// filename plus extension
	const CString csData = GetDataName( lpszPathName );
	const CString csPath = csFolder + _T( "\\" ) + csData;

	CLSID clsid = m_Extension.ClassID;
	Status status = pImage->Save( T2CW( csPath ), &clsid, &param );
	return status == Ok;
} // Save

/////////////////////////////////////////////////////////////////////////////
// crawl through the directory tree
void RecursePath( LPCTSTR path )
{
	USES_CONVERSION;

	// valid file extensions
	const CString csValidExt = _T( ".jpg;.jpeg;.png;.gif;.bmp;.tif;.tiff" );

	// the new folder under the image folder to contain the corrected images
	const CString csCorrected = GetCorrectedFolder();
	const int nCorrected = GetCorrectedFolderLength();

	CString csPathname( path );
	csPathname.TrimRight( _T( "\\" ) );

	// build a string with wild-cards
	CString strWildcard;
	strWildcard.Format( _T( "%s\\*.*" ), path );

	// start trolling for files we are interested in
	CFileFind finder;
	BOOL bWorking = finder.FindFile( strWildcard );
	while ( bWorking )
	{
		bWorking = finder.FindNextFile();

		// skip "." and ".." folder names
		if ( finder.IsDots() )
		{
			continue;
		}

		// if it's a directory, recursively search it
		if ( finder.IsDirectory() )
		{
			const CString str = finder.GetFilePath();

			// do not recurse into the corrected folder
			if ( str.Right( nCorrected ) == csCorrected )
			{
				continue;
			}

			// recurse into the new directory
			RecursePath( str );

		} else // write the properties if it is a valid extension
		{
			const CString csPath = finder.GetFilePath();
			const CString csExt = GetExtension( csPath ).MakeLower();
			const CString csFile = GetFileName( csPath );

			if ( -1 != csValidExt.Find( csExt ) )
			{
				m_Extension.FileExtension = csExt;

				CStdioFile fout( stdout );
				fout.WriteString( csPath + _T( "\n" ) );

				COleDateTime oDT = m_Mask.EncodedDateTime[ csFile ];
				COleDateTime::DateTimeStatus eStatus = oDT.GetStatus();
				if ( eStatus != COleDateTime::valid )
				{
					fout.WriteString
					(
						_T( "Invalid date and time parsed from filename\n" )
					);
					continue;
				}

				CString csDate = oDT.Format( _T( "%Y:%m:%d %H:%M:%S" ) );

				CString csOutput;
				csOutput.Format( _T( "New Date: %s\n" ), csDate );
				fout.WriteString( csOutput );

				// smart pointer to the image representing this element
				unique_ptr<Gdiplus::Image> pImage =
					unique_ptr<Gdiplus::Image>
					(
						Gdiplus::Image::FromFile( T2CW( csPath ) )
						);

				// smart pointer to the original date property item
				unique_ptr<Gdiplus::PropertyItem> pOriginalDateItem =
					unique_ptr<Gdiplus::PropertyItem>( new Gdiplus::PropertyItem );
				pOriginalDateItem->id = PropertyTagExifDTOrig;
				pOriginalDateItem->type = PropertyTagTypeASCII;
				pOriginalDateItem->length = csDate.GetLength() + 1;
				pOriginalDateItem->value = csDate.GetBuffer( pOriginalDateItem->length );

				// smart pointer to the digitized date property item
				unique_ptr<Gdiplus::PropertyItem> pDigitizedDateItem =
					unique_ptr<Gdiplus::PropertyItem>( new Gdiplus::PropertyItem );
				pDigitizedDateItem->id = PropertyTagExifDTDigitized;
				pDigitizedDateItem->type = PropertyTagTypeASCII;
				pDigitizedDateItem->length = csDate.GetLength() + 1;
				pDigitizedDateItem->value = csDate.GetBuffer( pDigitizedDateItem->length );

				// if these properties exist they will be replaced
				// if these properties do not exist they will be created
				pImage->SetPropertyItem( pOriginalDateItem.get() );
				pImage->SetPropertyItem( pDigitizedDateItem.get() );

				// save the image to the new path
				Save( csPath, pImage.get() );

				// release the date buffer
				csDate.ReleaseBuffer();
			}
		}
	}

	finder.Close();

} // RecursePath

/////////////////////////////////////////////////////////////////////////////
// mask used to parse the date from the filename
// the mask is populated for all date and time
// information and if any are not found, the Okay
// status is set to false;
void CMask::SetMask( CString value )
{
	m_csMask = value;
	CStdioFile fOut( stderr );
	CString csMessage;
	csMessage.Format( _T( "Mask value: %s\n" ), value );
	fOut.WriteString( _T( ".\n" ) );
	fOut.WriteString( csMessage );
	fOut.WriteString( _T( ".\n" ) );

	// being optimistic until proven wrong
	Okay = true;

	// try to find a 4 digit year first
	YearStart = value.Find( _T( "YYYY" ) );
	if ( YearStart == -1 )
	{
		// try to find a 2 digit year
		YearStart = value.Find( _T( "YY" ) );
		if ( YearStart != -1 )
		{
			YearLength = 2;

		} else
		{
			Okay = false;
			csMessage.Format( _T( "Failed Year Start: %d\n" ), YearStart );
			fOut.WriteString( _T( ".\n" ) );
			fOut.WriteString( csMessage );
			fOut.WriteString( _T( ".\n" ) );
		}
	} else
	{
		YearLength = 4;
	}

	// try to find a 2 digit month
	MonthStart = value.Find( _T( "MM" ) );
	if ( MonthStart != -1 )
	{
		MonthLength = 2;

	} else
	{
		Okay = false;
		fOut.WriteString( _T( ".\n" ) );
		fOut.WriteString( _T( "Failed Month Start\n" ) );
		fOut.WriteString( _T( ".\n" ) );
	}

	// try to find a 2 digit Day
	DayStart = value.Find( _T( "DD" ) );
	if ( DayStart != -1 )
	{
		DayLength = 2;

	} else
	{
		Okay = false;
		fOut.WriteString( _T( ".\n" ) );
		fOut.WriteString( _T( "Failed Day Start\n" ) );
		fOut.WriteString( _T( ".\n" ) );
	}

	// try to find a 2 digit Hour
	HourStart = value.Find( _T( "hh" ) );
	if ( HourStart != -1 )
	{
		HourLength = 2;

	} else
	{
		Okay = false;
		fOut.WriteString( _T( ".\n" ) );
		fOut.WriteString( _T( "Failed Hour Start\n" ) );
		fOut.WriteString( _T( ".\n" ) );
	}

	// try to find a 2 digit Minute
	MinuteStart = value.Find( _T( "mm" ) );
	if ( MinuteStart != -1 )
	{
		MinuteLength = 2;

	} else
	{
		Okay = false;
		fOut.WriteString( _T( ".\n" ) );
		fOut.WriteString( _T( "Failed Minute Start\n" ) );
		fOut.WriteString( _T( ".\n" ) );
	}

	// try to find a 2 digit Second
	SecondStart = value.Find( _T( "ss" ) );
	if ( SecondStart != -1 )
	{
		SecondLength = 2;

	} else
	{
		Okay = false;
		fOut.WriteString( _T( ".\n" ) );
		fOut.WriteString( _T( "Failed Second Start\n" ) );
		fOut.WriteString( _T( ".\n" ) );
	}

} // CMask::SetMask

/////////////////////////////////////////////////////////////////////////////
// set the current file extension which will automatically lookup the
// related mime type and class ID and set their respective properties
void CExtension::SetFileExtension( CString value )
{
	m_csFileExtension = value;

	if ( m_mapExtensions.Exists[ value ] )
	{
		MimeType = *m_mapExtensions.find( value );

		// populate the mime type map the first time it is referenced
		if ( m_mapMimeTypes.Count == 0 )
		{
			UINT num = 0;
			UINT size = 0;

			// gets the number of available image encoders and 
			// the total size of the array
			Gdiplus::GetImageEncodersSize( &num, &size );
			if ( size == 0 )
			{
				return;
			}

			ImageCodecInfo* pImageCodecInfo =
				(ImageCodecInfo*)malloc( size );
			if ( pImageCodecInfo == nullptr )
			{
				return;
			}

			// Returns an array of ImageCodecInfo objects that contain 
			// information about the image encoders built into GDI+.
			Gdiplus::GetImageEncoders( num, size, pImageCodecInfo );

			// populate the map of mime types the first time it is 
			// needed
			for ( UINT nIndex = 0; nIndex < num; ++nIndex )
			{
				CString csKey;
				csKey = CW2A( pImageCodecInfo[ nIndex ].MimeType );
				CLSID classID = pImageCodecInfo[ nIndex ].Clsid;
				m_mapMimeTypes.add( csKey, new CLSID( classID ) );
			}

			// clean up
			free( pImageCodecInfo );
		}

		ClassID = *m_mapMimeTypes.find( MimeType );

	} else
	{
		MimeType = _T( "" );
	}
} // CExtension::SetFileExtension

/////////////////////////////////////////////////////////////////////////////
// a console application that can crawl through the file
// system and troll for image metadata properties
int _tmain( int argc, TCHAR* argv[], TCHAR* envp[] )
{
	HMODULE hModule = ::GetModuleHandle( NULL );
	if ( hModule == NULL )
	{
		_tprintf( _T( "Fatal Error: GetModuleHandle failed\n" ) );
		return 1;
	}

	// initialize MFC and error on failure
	if ( !AfxWinInit( hModule, NULL, ::GetCommandLine(), 0 ) )
	{
		_tprintf( _T( "Fatal Error: MFC initialization failed\n " ) );
		return 2;
	}

	CStdioFile fOut( stdout );
	if ( argc != 3 )
	{
		fOut.WriteString( _T( ".\n" ) );
		fOut.WriteString
		(
			_T( "FixDateTaken, Copyright (c) 2020, " )
			_T( "by W. T. Block.\n" )
		);
		fOut.WriteString( _T( ".\n" ) );
		fOut.WriteString( _T( "Usage:\n" ) );
		fOut.WriteString( _T( ".\n" ) );
		fOut.WriteString( _T( ".  FixDateTaken pathname mask\n" ) );
		fOut.WriteString( _T( ".\n" ) );
		fOut.WriteString( _T( "Where:\n" ) );
		fOut.WriteString( _T( ".\n" ) );
		fOut.WriteString
		(
			_T( ".  pathname is the root of the tree to be scanned\n" )
		);
		fOut.WriteString
		(
			_T( ".  mask is the string that defines where the date\n" )
			_T( ".    is encoded into the file name, where:\n" )
			_T( ".      YY is used for two digit year:\n" )
			_T( ".      YYYY is used for four digit year:\n" )
			_T( ".      MM is used for month:\n" )
			_T( ".      DD is used for day:\n" )
			_T( ".      hh is used for hour:\n" )
			_T( ".      mm is used for minute:\n" )
			_T( ".      ss is used for second:\n" )
			_T( ".  examples:\n" )
		);
		fOut.WriteString
		(
			_T( ".    YYMMDD-hhmm-ss\n" )
			_T( ".      for files named like: 121201-2148-58.jpg\n" )
			_T( ".    YYYY_MM_DD_hh_mm_ss\n" )
			_T( ".      for files named like: 1980_01_01_00_40_08.jpg\n" )
			_T( ".    DCIM_YYYYMMDD_hhmmss\n" )
			_T( ".      for files named like: DCIM_20191228_124705.jpg\n" )
			_T( ".    WP_YYYYMMDD_hh_mm_ss\n" )
			_T( ".      for files named like: WP_19501117_11_40_56_Pro.jpg\n" )
		);
		fOut.WriteString( _T( ".\n" ) );
		return 3;
	}

	// display the executable path
	CString csMessage;
	csMessage.Format( _T( "Executable pathname: %s\n" ), argv[ 0 ] );
	fOut.WriteString( _T( ".\n" ) );
	fOut.WriteString( csMessage );
	fOut.WriteString( _T( ".\n" ) );

	// retrieve the pathname and validate the pathname exists
	CString csPath = argv[ 1 ];
	if ( !::PathFileExists( csPath ) )
	{
		csMessage.Format( _T( "Invalid pathname: %s\n" ), csPath );
		fOut.WriteString( _T( ".\n" ) );
		fOut.WriteString( csMessage );
		fOut.WriteString( _T( ".\n" ) );
		return 4;

	} else
	{
		csMessage.Format( _T( "Given pathname: %s\n" ), csPath );
		fOut.WriteString( _T( ".\n" ) );
		fOut.WriteString( csMessage );
		fOut.WriteString( _T( ".\n" ) );
	}

	// retrieve the date and time mask that describes the location
	// of date and time information encoded into the filename. 
	m_Mask.Mask = argv[ 2 ];

	// If all of the date and time mask information is present,
	// the Okay status of the class will be set to true.
	if ( m_Mask.Okay == false )
	{
		csMessage.Format( _T( "Invalid mask parameter: %s\n" ), m_Mask.Mask );
		fOut.WriteString( _T( ".\n" ) );
		fOut.WriteString( csMessage );
		fOut.WriteString( _T( ".\n" ) );
		return 5;
	} else
	{
		csMessage.Format( _T( "The mask parameter is: %s\n" ), m_Mask.Mask );
		fOut.WriteString( _T( ".\n" ) );
		fOut.WriteString( csMessage );
		fOut.WriteString( _T( ".\n" ) );
	}

	// start up COM
	AfxOleInit();
	::CoInitialize( NULL );

	// reference to GDI+
	InitGdiplus();

	// crawl through directory tree defined by the command line
	// parameter trolling for image files
	RecursePath( csPath );

	// clean up references to GDI+
	TerminateGdiplus();

	// all is good
	return 0;

} // _tmain

/////////////////////////////////////////////////////////////////////////////
