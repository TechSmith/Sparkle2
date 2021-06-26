//
//  SPUCoreBasedUpdateDriver.h
//  Sparkle
//
//  Created by Mayur Pawashe on 3/18/16.
//  Copyright © 2016 Sparkle Project. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SPUUserUpdateState.h"
#import "SPUUpdateDriver.h"

NS_ASSUME_NONNULL_BEGIN

@class SUHost, SUAppcastItem;
@protocol SPUUpdaterDelegate;

@protocol SPUCoreBasedUpdateDriverDelegate <NSObject>

- (void)basicDriverDidFindUpdateWithAppcastItem:(SUAppcastItem *)updateItem secondaryAppcastItem:(SUAppcastItem * _Nullable)secondaryAppcastItem preventsAutoupdate:(BOOL)preventsAutoupdate;

- (void)installerDidFinishPreparationAndWillInstallImmediately:(BOOL)willInstallImmediately silently:(BOOL)willInstallSilently;

- (void)coreDriverIsRequestingAbortUpdateWithError:(nullable NSError *)error;

- (void)basicDriverIsRequestingAbortUpdateWithError:(nullable NSError *)error;

@optional

- (void)basicDriverDidFinishLoadingAppcast;

- (void)downloadDriverWillBeginDownload;

- (void)downloadDriverDidReceiveExpectedContentLength:(uint64_t)expectedContentLength;

- (void)downloadDriverDidReceiveDataOfLength:(uint64_t)length;

- (void)coreDriverDidStartExtractingUpdate;

- (void)installerDidStartInstalling;

- (void)installerDidExtractUpdateWithProgress:(double)progress;

- (void)installerIsSendingAppTerminationSignal;

- (void)installerDidFinishInstallationAndRelaunched:(BOOL)relaunched acknowledgement:(void(^)(void))acknowledgement;

@end

@interface SPUCoreBasedUpdateDriver : NSObject

- (instancetype)initWithHost:(SUHost *)host applicationBundle:(NSBundle *)applicationBundle sparkleBundle:(NSBundle *)sparkleBundle updater:(id)updater updaterDelegate:(nullable id <SPUUpdaterDelegate>)updaterDelegate delegate:(id<SPUCoreBasedUpdateDriverDelegate>)delegate;

- (void)prepareCheckForUpdatesWithCompletion:(SPUUpdateDriverCompletion)completionBlock;

- (void)preflightForUpdatePermissionPreventingInstallerInteraction:(BOOL)preventsInstallerInteraction reply:(void (^)(NSError * _Nullable))reply;

- (void)checkForUpdatesAtAppcastURL:(NSURL *)appcastURL withUserAgent:(NSString *)userAgent httpHeaders:(NSDictionary * _Nullable)httpHeaders inBackground:(BOOL)background requiresSilentInstall:(BOOL)silentInstall;

- (void)resumeInstallingUpdateWithCompletion:(SPUUpdateDriverCompletion)completionBlock;

- (void)resumeUpdate:(id<SPUResumableUpdate>)resumableUpdate completion:(SPUUpdateDriverCompletion)completionBlock;

- (void)downloadUpdateFromAppcastItem:(SUAppcastItem *)updateItem secondaryAppcastItem:(SUAppcastItem * _Nullable)secondaryUpdateItem inBackground:(BOOL)background;

- (void)deferInformationalUpdate:(SUAppcastItem *)updateItem secondaryUpdate:(SUAppcastItem * _Nullable)secondaryUpdateItem preventsAutoupdate:(BOOL)preventsAutoupdate;

- (void)extractDownloadedUpdate;

- (void)clearDownloadedUpdate;

- (void)finishInstallationWithResponse:(SPUUserUpdateChoice)installUpdateStatus displayingUserInterface:(BOOL)displayingUserInterface;

- (void)abortUpdateAndShowNextUpdateImmediately:(BOOL)shouldShowUpdateImmediately error:(nullable NSError *)error;

@end

NS_ASSUME_NONNULL_END
