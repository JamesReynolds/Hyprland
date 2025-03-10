#pragma once

#include "../defines.hpp"
#include "../Window.hpp"

struct SWindowRenderLayoutHints {
    bool        isBorderColor = false;
    CColor      borderColor;
};

struct SLayoutMessageHeader {
    CWindow*    pWindow = nullptr;
};

enum eFullscreenMode : uint8_t;

interface IHyprLayout {
public:

    /*
        Called when a window is created (mapped)
        The layout HAS TO set the goal pos and size (anim mgr will use it)
        If !animationinprogress, then the anim mgr will not apply an anim.
    */
    virtual void        onWindowCreated(CWindow*)           = 0;
    /*
        Called when a window is removed (unmapped)
    */
    virtual void        onWindowRemoved(CWindow*)           = 0;
    /*
        Called when the monitor requires a layout recalculation
        this usually means reserved area changes
    */
    virtual void        recalculateMonitor(const int&)      = 0;

    /*
        Called when the compositor requests a window
        to be recalculated, e.g. when pseudo is toggled.
    */
    virtual void        recalculateWindow(CWindow*)         = 0;

    /*
        Called when a window is requested to be floated
    */
    virtual void        changeWindowFloatingMode(CWindow*)  = 0;
    /*
        Called when a window is clicked on, beginning a drag
        this might be a resize, move, whatever the layout defines it
        as.
    */
    virtual void        onBeginDragWindow()                 = 0;
    /*
        Called when a window is ended being dragged
        (mouse up)
    */
    virtual void        onEndDragWindow()                   = 0;
    /*
        Called whenever the mouse moves, should the layout want to 
        do anything with it.
        Useful for dragging.
    */
    virtual void        onMouseMove(const Vector2D&)        = 0;
    /*
        Called when a window is created, but is requesting to be floated.
        Warning: this also includes stuff like popups, incorrect handling
        of which can result in a crash!
    */
    virtual void        onWindowCreatedFloating(CWindow*)   = 0;

    /*
        Called when a window / the user requests to toggle the fullscreen state of a window
        The layout sets all the fullscreen flags.
        It can either accept or ignore.
    */
    virtual void        fullscreenRequestForWindow(CWindow*, eFullscreenMode)    = 0;

    /*
        Called when a dispatcher requests a custom message
        The layout is free to ignore. 
        std::any is the reply. Can be empty.
    */
    virtual std::any    layoutMessage(SLayoutMessageHeader, std::string)  = 0;

    /* 
        Required to be handled, but may return just SWindowRenderLayoutHints()
        Called when the renderer requests any special draw flags for
        a specific window, e.g. border color for groups.
    */
    virtual SWindowRenderLayoutHints requestRenderHints(CWindow*) = 0;

    /* 
        Called when the user requests two windows to be swapped places.
        The layout is free to ignore.
    */
    virtual void         switchWindows(CWindow*, CWindow*)      = 0;

    /*
        Called when the user requests to change the splitratio by X
        on a window
    */
    virtual void         alterSplitRatioBy(CWindow*, float)     = 0;

    /*
        Called when something wants the current layout's name
    */
    virtual std::string  getLayoutName() = 0;
};