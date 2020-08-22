/////////////////////////////////////////////////////////////////////////////
// Copyright © by W. T. Block, all rights reserved
/////////////////////////////////////////////////////////////////////////////
#pragma once

#include "resource.h"
#include "KeyedCollection.h"
#include <vector>
#include <map>
#include <memory>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;
using namespace std;

/////////////////////////////////////////////////////////////////////////////
// this class parses the mask provided on the command line to determine
// where in the filename the date and time information is encoded
class CMask
{
	// protected data
protected:
	// mask used to parse the date and time from the 
	// filename passed in containing encoded date and time
	CString m_csMask;

	// zero based start of year in mask
	int m_nYearStart;

	// Length of year in mask
	int m_nYearLength;

	// zero based start of month in mask
	int m_nMonthStart;

	// Length of month in mask
	int m_nMonthLength;

	// zero based start of day in mask
	int m_nDayStart;

	// Length of day in mask
	int m_nDayLength;

	// zero based start of hour in mask
	int m_nHourStart;

	// Length of hour in mask
	int m_nHourLength;

	// zero based start of minute in mask
	int m_nMinuteStart;

	// Length of minute in mask
	int m_nMinuteLength;

	// zero based start of second in mask
	int m_nSecondStart;

	// Length of second in mask
	int m_nSecondLength;

	// boolean indicator that all mask properties were set
	bool m_bOkay;

	// public properties
public:
	// mask used to parse the date and time from the 
	// filename passed in containing encoded date and time
	inline CString GetMask()
	{
		return m_csMask;
	}
	// mask used to parse the date from the file name
	// the mask is populated for all date and time
	// information and if any are not found, the Okay
	// status is set to false;
	void SetMask( CString value );
	// mask used to parse the date and time from the 
	// filename passed in containing encoded date and time
	__declspec( property( get = GetMask, put = SetMask ) )
		CString Mask;

	// zero based start of year in mask
	inline int GetYearStart()
	{
		return m_nYearStart;
	}
	// zero based start of year in mask
	inline void SetYearStart( int value )
	{
		m_nYearStart = value;
	}
	// zero based start of year in mask
	__declspec( property( get = GetYearStart, put = SetYearStart ) )
		int YearStart;

	// Length of year in mask
	inline int GetYearLength()
	{
		return m_nYearLength;
	}
	// Length of year in mask
	inline void SetYearLength( int value )
	{
		m_nYearLength = value;
	}
	// Length of year in mask
	__declspec( property( get = GetYearLength, put = SetYearLength ) )
		int YearLength;

	// zero based start of Month in mask
	inline int GetMonthStart()
	{
		return m_nMonthStart;
	}
	// zero based start of Month in mask
	inline void SetMonthStart( int value )
	{
		m_nMonthStart = value;
	}
	// zero based start of Month in mask
	__declspec( property( get = GetMonthStart, put = SetMonthStart ) )
		int MonthStart;

	// Length of Month in mask
	inline int GetMonthLength()
	{
		return m_nMonthLength;
	}
	// Length of Month in mask
	inline void SetMonthLength( int value )
	{
		m_nMonthLength = value;
	}
	// Length of Month in mask
	__declspec( property( get = GetMonthLength, put = SetMonthLength ) )
		int MonthLength;

	// zero based start of Day in mask
	inline int GetDayStart()
	{
		return m_nDayStart;
	}
	// zero based start of Day in mask
	inline void SetDayStart( int value )
	{
		m_nDayStart = value;
	}
	// zero based start of Day in mask
	__declspec( property( get = GetDayStart, put = SetDayStart ) )
		int DayStart;

	// Length of Day in mask
	inline int GetDayLength()
	{
		return m_nDayLength;
	}
	// Length of Day in mask
	inline void SetDayLength( int value )
	{
		m_nDayLength = value;
	}
	// Length of Day in mask
	__declspec( property( get = GetDayLength, put = SetDayLength ) )
		int DayLength;

	// zero based start of Hour in mask
	inline int GetHourStart()
	{
		return m_nHourStart;
	}
	// zero based start of Hour in mask
	inline void SetHourStart( int value )
	{
		m_nHourStart = value;
	}
	// zero based start of Hour in mask
	__declspec( property( get = GetHourStart, put = SetHourStart ) )
		int HourStart;

	// Length of Hour in mask
	inline int GetHourLength()
	{
		return m_nHourLength;
	}
	// Length of Hour in mask
	inline void SetHourLength( int value )
	{
		m_nHourLength = value;
	}
	// Length of Hour in mask
	__declspec( property( get = GetHourLength, put = SetHourLength ) )
		int HourLength;

	// zero based start of Minute in mask
	inline int GetMinuteStart()
	{
		return m_nMinuteStart;
	}
	// zero based start of Minute in mask
	inline void SetMinuteStart( int value )
	{
		m_nMinuteStart = value;
	}
	// zero based start of Minute in mask
	__declspec( property( get = GetMinuteStart, put = SetMinuteStart ) )
		int MinuteStart;

	// Length of Minute in mask
	inline int GetMinuteLength()
	{
		return m_nMinuteLength;
	}
	// Length of Minute in mask
	inline void SetMinuteLength( int value )
	{
		m_nMinuteLength = value;
	}
	// Length of Minute in mask
	__declspec( property( get = GetMinuteLength, put = SetMinuteLength ) )
		int MinuteLength;

	// zero based start of Second in mask
	inline int GetSecondStart()
	{
		return m_nSecondStart;
	}
	// zero based start of Second in mask
	inline void SetSecondStart( int value )
	{
		m_nSecondStart = value;
	}
	// zero based start of Second in mask
	__declspec( property( get = GetSecondStart, put = SetSecondStart ) )
		int SecondStart;

	// Length of Second in mask
	inline int GetSecondLength()
	{
		return m_nSecondLength;
	}
	// Length of Second in mask
	inline void SetSecondLength( int value )
	{
		m_nSecondLength = value;
	}
	// Length of Second in mask
	__declspec( property( get = GetSecondLength, put = SetSecondLength ) )
		int SecondLength;

	// boolean indicator that all mask properties were set
	inline bool GetOkay()
	{
		return m_bOkay;
	}
	// boolean indicator that all mask properties were set
	inline void SetOkay( bool value )
	{
		m_bOkay = value;
	}
	// boolean indicator that all mask properties were set
	__declspec( property( get = GetOkay, put = SetOkay ) )
		bool Okay;

	// given a filename, parse the date and time encoded
	// into the name based on the mask properties
	inline COleDateTime GetEncodedDateTime( CString fileName )
	{
		COleDateTime value;

		// if the mask string failed to parse, get out
		if ( !Okay )
		{
			return value;
		}

		// parse the year from the given fileName
		int year = _tstol( fileName.Mid( YearStart, YearLength ) );

		// two character years need to be handled
		if ( year < 100 )
		{
			COleDateTime now( COleDateTime::GetCurrentTime() );
			const int nCurrentYear = now.GetYear();

			// try adding 2000 to the year
			int yearTemp = year + 2000;

			// if yearTemp is greater than the current year
			// then add 1900 to the two character year
			if ( yearTemp > nCurrentYear )
			{
				year += 1900;
			} else // assume the year offset is 2000
			{
				year += 2000;
			}
		}

		// parse the remainder of the date and time
		const int month = _tstol( fileName.Mid( MonthStart, MonthLength ) );
		const int day = _tstol( fileName.Mid( DayStart, DayLength ) );
		const int hour = _tstol( fileName.Mid( HourStart, HourLength ) );
		const int minute = _tstol( fileName.Mid( MinuteStart, MinuteLength ) );
		const int second = _tstol( fileName.Mid( SecondStart, SecondLength ) );

		// set the return value based on what we found above
		value.SetDateTime( year, month, day, hour, minute, second );

		// give it back
		return value;
	}
	// given a filename, parse the date and time encoded
	// into the name based on the mask properties
	__declspec( property( get = GetEncodedDateTime ) )
		COleDateTime EncodedDateTime[];

	// public methods
public:
	// constructor
	CMask()
	{
		YearStart = -1;
		YearLength = -1;
		MonthStart = -1;
		MonthLength = -1;
		DayStart = -1;
		DayLength = -1;
		HourStart = -1;
		HourLength = -1;
		MinuteStart = -1;
		MinuteLength = -1;
		SecondStart = -1;
		SecondLength = -1;

		Okay = false;
	}
};

/////////////////////////////////////////////////////////////////////////////
// this class creates a fast look up of the mime type and class ID as 
// defined by GDI+ for common file extensions
class CExtension
{
	// protected definitions
protected:
	typedef struct tagExtensionLookup
	{
		CString m_csFileExtension;
		CString m_csMimeType;

	} EXTENSION_LOOKUP;

	typedef struct tagClassLookup
	{
		CString m_csMimeType;
		CLSID m_ClassID;

	} CLASS_LOOKUP;

	// protected data
protected:
	// current file extension
	CString m_csFileExtension;

	// current mime type
	CString m_csMimeType;

	// current class ID
	CLSID m_ClassID;

	// cross reference of file extensions to mime types
	CKeyedCollection<CString, CString> m_mapExtensions;

	// cross reference of mime types to class IDs
	CKeyedCollection<CString, CLSID> m_mapMimeTypes;

	// public properties
public:
	// current file extension
	inline CString GetFileExtension()
	{
		return m_csFileExtension;
	}
	// current file extension
	void SetFileExtension( CString value );
	// current file extension
	__declspec( property( get = GetFileExtension, put = SetFileExtension ) )
		CString FileExtension;

	// image extension associated with the current file extension
	inline CString GetMimeType()
	{
		return m_csMimeType;
	}
	// image extension associated with the current file extension
	inline void SetMimeType( CString value )
	{
		m_csMimeType = value;
	}
	// get image extension associated with the current file extension
	__declspec( property( get = GetMimeType, put = SetMimeType ) )
		CString MimeType;

	// class ID associated with the current file extension
	inline CLSID GetClassID()
	{
		return m_ClassID;
	}
	// class ID associated with the current file extension
	inline void SetClassID( CLSID value )
	{
		m_ClassID = value;
	}
	// class ID associated with the current file extension
	__declspec( property( get = GetClassID, put = SetClassID ) )
		CLSID ClassID;

	// public methods
public:

	// protected methods
protected:

	// public virtual methods
public:

	// protected virtual methods
protected:

	// public construction
public:
	CExtension()
	{
		USES_CONVERSION;

		// extension conversion table
		static EXTENSION_LOOKUP ExtensionLookup[] =
		{
			{ _T( ".bmp" ), _T( "image/bmp" ) },
			{ _T( ".dib" ), _T( "image/bmp" ) },
			{ _T( ".rle" ), _T( "image/bmp" ) },
			{ _T( ".gif" ), _T( "image/gif" ) },
			{ _T( ".jpeg" ), _T( "image/jpeg" ) },
			{ _T( ".jpg" ), _T( "image/jpeg" ) },
			{ _T( ".jpe" ), _T( "image/jpeg" ) },
			{ _T( ".jfif" ), _T( "image/jpeg" ) },
			{ _T( ".png" ), _T( "image/png" ) },
			{ _T( ".tiff" ), _T( "image/tiff" ) },
			{ _T( ".tif" ), _T( "image/tiff" ) }
		};

		// build a cross reference of file extensions to 
		// mime types
		const int nPairs = _countof( ExtensionLookup );
		for ( int nPair = 0; nPair < nPairs; nPair++ )
		{
			const CString csKey =
				ExtensionLookup[ nPair ].m_csFileExtension;

			CString* pValue = new CString
			(
				ExtensionLookup[ nPair ].m_csMimeType
			);

			// add the pair to the collection
			m_mapExtensions.add( csKey, pValue );
		}
	}
};

/////////////////////////////////////////////////////////////////////////////
// used for gdiplus library
ULONG_PTR m_gdiplusToken;

/////////////////////////////////////////////////////////////////////////////
// this class parses the mask provided on the command line to determine
// where in the filename the date and time information is encoded
CMask m_Mask;

/////////////////////////////////////////////////////////////////////////////
// this class creates a fast look up of the mime type and class ID as 
// defined by GDI+ for common file extensions
CExtension m_Extension;

/////////////////////////////////////////////////////////////////////////////
// when true, sub-folders will be processed as well as the base folder
bool m_bRecurse;

/////////////////////////////////////////////////////////////////////////////
// the new folder under the image folder to contain the corrected images
static inline CString GetCorrectedFolder()
{
	return _T( "Corrected" );
}

/////////////////////////////////////////////////////////////////////////////
// the new folder under the image folder to contain the corrected images
static inline int GetCorrectedFolderLength()
{
	const CString csFolder = GetCorrectedFolder();
	const int value = csFolder.GetLength();
	return value;
}

/////////////////////////////////////////////////////////////////////////////
// parse the filename from a pathname
static inline CString GetFileName( LPCTSTR pcszPath )
{
	CString csPath( pcszPath );
	TCHAR* pBuf = csPath.GetBuffer( csPath.GetLength() + 1 );
	TCHAR szDrive[ _MAX_DRIVE ];
	TCHAR szDir[ _MAX_DIR ];
	TCHAR szFile[ _MAX_FNAME ];
	TCHAR szExt[ _MAX_EXT ];

	_tsplitpath( pBuf, szDrive, szDir, szFile, szExt );
	csPath.ReleaseBuffer();
	return szFile;
}

/////////////////////////////////////////////////////////////////////////////
// parse the extension from a pathname
static inline CString GetExtension( LPCTSTR pcszPath )
{
	CString csPath( pcszPath );
	TCHAR* pBuf = csPath.GetBuffer( csPath.GetLength() + 1 );
	TCHAR szDrive[ _MAX_DRIVE ];
	TCHAR szDir[ _MAX_DIR ];
	TCHAR szFile[ _MAX_FNAME ];
	TCHAR szExt[ _MAX_EXT ];

	_tsplitpath( pBuf, szDrive, szDir, szFile, szExt );
	csPath.ReleaseBuffer();
	return szExt;
}

/////////////////////////////////////////////////////////////////////////////
// parse the directory from a pathname
static inline CString GetDirectory( LPCTSTR pcszPath )
{
	CString csPath( pcszPath );
	TCHAR* pBuf = csPath.GetBuffer( csPath.GetLength() + 1 );
	TCHAR szDrive[ _MAX_DRIVE ];
	TCHAR szDir[ _MAX_DIR ];
	TCHAR szFile[ _MAX_FNAME ];
	TCHAR szExt[ _MAX_EXT ];

	_tsplitpath( pBuf, szDrive, szDir, szFile, szExt );
	csPath.ReleaseBuffer();
	return szDir;
}

/////////////////////////////////////////////////////////////////////////////
// parse the drive from a pathname
static inline CString GetDrive( LPCTSTR pcszPath )
{
	CString csPath( pcszPath );
	TCHAR* pBuf = csPath.GetBuffer( csPath.GetLength() + 1 );
	TCHAR szDrive[ _MAX_DRIVE ];
	TCHAR szDir[ _MAX_DIR ];
	TCHAR szFile[ _MAX_FNAME ];
	TCHAR szExt[ _MAX_EXT ];

	_tsplitpath( pBuf, szDrive, szDir, szFile, szExt );
	csPath.ReleaseBuffer();
	return szDrive;
}

/////////////////////////////////////////////////////////////////////////////
// parse folder from a pathname (drive and directory)
static inline CString GetFolder( LPCTSTR pcszPath )
{
	CString csDrive = GetDrive( pcszPath );
	CString csDir = GetDirectory( pcszPath );
	return csDrive + csDir;
}

/////////////////////////////////////////////////////////////////////////////
// parse data name from a pathname (filename and extension)
static inline CString GetDataName( LPCTSTR pcszPath )
{
	CString csFile = GetFileName( pcszPath );
	CString csExt = GetExtension( pcszPath );
	return csFile + csExt;
}

/////////////////////////////////////////////////////////////////////////////
// This function creates a file system folder whose fully qualified 
// path is given by pszPath. If one or more of the intermediate 
// folders do not exist, they will be created as well. 
// returns true if the path is created or already exists
bool CreatePath( LPCTSTR pszPath )
{
	if ( ERROR_SUCCESS == SHCreateDirectoryEx( NULL, pszPath, NULL ) )
	{
		return true;
	}

	return false;
} // CreatePath

/////////////////////////////////////////////////////////////////////////////
// initialize GDI+
bool InitGdiplus()
{
	GdiplusStartupInput gdiplusStartupInput;
	Status status = GdiplusStartup
	(
		&m_gdiplusToken,
		&gdiplusStartupInput,
		NULL
	);
	return ( Ok == status );
} // InitGdiplus

/////////////////////////////////////////////////////////////////////////////
// remove reference to GDI+
void TerminateGdiplus()
{
	GdiplusShutdown( m_gdiplusToken );
	m_gdiplusToken = NULL;

}// TerminateGdiplus

/////////////////////////////////////////////////////////////////////////////
