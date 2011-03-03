//
//  WILDAboutPanelController.m
//  Stacksmith
//
//  Created by Uli Kusterer on 01.03.11.
//  Copyright 2011 Uli Kusterer. All rights reserved.
//

#import "WILDAboutPanelController.h"
#import "UKLicense.h"


@implementation WILDAboutPanelController

@synthesize licenseeField = mLicenseeField;
@synthesize companyField = mCompanyField;
@synthesize versionField = mVersionField;

+(void)	showAboutPanel
{
	static WILDAboutPanelController	*	sAboutPanel = nil;
	if( !sAboutPanel )
	{
		sAboutPanel = [[WILDAboutPanelController alloc] init];
		[sAboutPanel showWindow: nil];
	}
	
	[[sAboutPanel window] makeKeyAndOrderFront: nil];
}

- (id)init
{
    self = [super initWithWindowNibName: @"WILDAboutPanelController"];
    if( self )
	{
        [self setShouldCascadeWindows: NO];
    }
    
    return self;
}

- (void)dealloc
{
	DESTROY(mLicenseeField);
	DESTROY(mCompanyField);
	DESTROY(mVersionField);
	
    [super dealloc];
}

- (void)windowDidLoad
{
    [super windowDidLoad];
    
	// Check serial number:
	struct UKLicenseInfo	theInfo;
	NSString			*	textString = [[NSUserDefaults standardUserDefaults] stringForKey: @"WILDLicenseKey"];
	NSData				*	textData = [textString dataUsingEncoding: NSASCIIStringEncoding];
	int						numBinaryBytes = UKBinaryLengthForReadableBytesOfLength( [textData length] );
	NSMutableData		*	binaryBytes = [NSMutableData dataWithLength: numBinaryBytes];
	UKBinaryDataForReadableBytesOfLength( [textData bytes], [textData length], [binaryBytes mutableBytes] );
	UKGetLicenseData( [binaryBytes mutableBytes], [binaryBytes length], &theInfo );

	NSString	*	person = [[[NSString alloc] initWithBytes: theInfo.ukli_licenseeName length: 40 encoding: NSUTF8StringEncoding] autorelease];
	NSString	*	company = [[[NSString alloc] initWithBytes: theInfo.ukli_licenseeCompany length: 40 encoding: NSUTF8StringEncoding] autorelease];
	NSCharacterSet*	ws = [NSCharacterSet whitespaceCharacterSet];
	person = [person stringByTrimmingCharactersInSet: ws];
	company = [company stringByTrimmingCharactersInSet: ws];
	if( [company length] == 0 )
	{
		[mLicenseeField setStringValue: @""];
		[mCompanyField setStringValue: person];
	}
	else
	{
		[mLicenseeField setStringValue: person];
		[mCompanyField setStringValue: company];
	}
	NSString*	version = [NSString stringWithFormat: @"%@ (%@)", [[NSBundle mainBundle] objectForInfoDictionaryKey: @"CFBundleShortVersionString"], [[NSBundle mainBundle] objectForInfoDictionaryKey: @"CFBundleVersion"]];
	[mVersionField setStringValue: version];
}

@end
