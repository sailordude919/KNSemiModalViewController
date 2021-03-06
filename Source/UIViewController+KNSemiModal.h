//
//  KNSemiModalViewController.h
//  KNSemiModalViewController
//
//  Created by Kent Nguyen on 2/5/12.
//  Copyright (c) 2012 Kent Nguyen. All rights reserved.
//

#define kSemiModalDidShowNotification @"kSemiModalDidShowNotification"
#define kSemiModalDidHideNotification @"kSemiModalDidHideNotification"
#define kSemiModalWasResizedNotification @"kSemiModalWasResizedNotification"
#define kSemiModalWillDismissNotification @"kSemiModalDidDismissNotification"
#define kSemiModalDidStartDismissing @"kn_semiModalDidStartDismissing"


extern const struct KNSemiModalOptionKeys {
	__unsafe_unretained NSString *traverseParentHierarchy; // boxed BOOL. default is YES.
	__unsafe_unretained NSString *pushParentBack;		   // boxed BOOL. default is YES.
	__unsafe_unretained NSString *animationDuration; // boxed double, in seconds. default is 0.5.
	__unsafe_unretained NSString *parentAlpha;       // boxed float. lower is darker. default is 0.5.
	__unsafe_unretained NSString *shadowOpacity;     // default is 0.8
	__unsafe_unretained NSString *transitionStyle;	 // boxed NSNumber - one of the KNSemiModalTransitionStyle values.
    __unsafe_unretained NSString *disableCancel;     // boxed BOOL. default is NO.
} KNSemiModalOptionKeys;

NS_ENUM(NSUInteger, KNSemiModalTransitionStyle) {
	KNSemiModalTransitionStyleSlideUp,
	KNSemiModalTransitionStyleFadeInOut,
	KNSemiModalTransitionStyleFadeIn,
	KNSemiModalTransitionStyleFadeOut,
};

typedef void (^KNTransitionCompletionBlock)(void);

@interface UIViewController (KNSemiModal)


/**
 Displays a view controller over the receiver, which is "dimmed".
 @param vc           The view controller to display semi-modally; its view's frame height is used.
 @param options	     See KNSemiModalOptionKeys constants.
 @param completion   Is called after `-[vc viewDidAppear:]`.
 @param dismissBlock Is called when the user dismisses the semi-modal view by tapping the dimmed receiver view.
 */
-(void)presentSemiViewController:(UIViewController*)vc
					 withOptions:(NSDictionary*)options
					  completion:(KNTransitionCompletionBlock)completion
					dismissBlock:(KNTransitionCompletionBlock)dismissBlock;

-(void)presentSemiView:(UIView*)view
		   withOptions:(NSDictionary*)options
			completion:(KNTransitionCompletionBlock)completion;

-(void)moveSemiViewWithPercentToFinish:(float)percent;
-(void)beginMoveSemiViewController:(UIViewController*)vc withPredefinedSnapshotView:(UIView*)snap;
-(void)beginMoveSemiViewController:(UIViewController*)vc;
-(void)finishMovingSemiViewControllerUpWithPercent:(float)percent;
-(void)finishMovingSemiViewControllerDownWithPercent:(float)percent;
-(void)dismissSemiModalViewByPanningWithPercent:(float)percent;

// Convenient overloading methods
-(void)presentSemiViewController:(UIViewController*)vc;
-(void)presentSemiViewController:(UIViewController*)vc withOptions:(NSDictionary*)options;
-(void)presentSemiViewController:(UIViewController*)vc withPredefinedSnapshotView:(UIView*)snap;
-(void)presentSemiViewController:(UIViewController*)vc withPredefinedImage:(UIImage*)image;
-(void)presentSemiView:(UIView*)vc;
-(void)presentSemiView:(UIView*)view withOptions:(NSDictionary*)options;
-(void)presentSemiViewController:(UIViewController*)vc
          withPreDefinedSnapshot:(UIView*)snap
					 withOptions:(NSDictionary*)options
					  completion:(KNTransitionCompletionBlock)completion
					dismissBlock:(KNTransitionCompletionBlock)dismissBlock;

// Dismiss & resize
-(void)resizeSemiView:(CGSize)newSize;
-(void)dismissSemiModalView;
-(void)dismissSemiModalViewWithCompletion:(KNTransitionCompletionBlock)completion;

@end

// Convenient category method to find actual ViewController that contains a view

@interface UIView (FindUIViewController)
- (UIViewController *) containingViewController;
- (id) traverseResponderChainForUIViewController;
@end