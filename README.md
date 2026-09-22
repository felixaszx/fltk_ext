# `Fl_Ext`

This is a library that intents to make fltk looks a little bit mordern with some new features.

This library also include a greate layout management library: [Fl_Flow](https://github.com/osen/Fl_Flow) by osen.

This library is released under the same license as fltk. 

## `fl`
This library introduces 2 new namespaces.

`fl` namespace is a wrapper of original fltk classes. 
```cpp
Fl_Double_Window window(800,600);
// is same as
fl::double_window window(800,600);

// with exception of Fl::
Fl::visiable_focus(true);
// is same as
fl::sys::visiable_focus(true);

// note that Fl_Flow is also included
Fl_Flow flow;
// is same as
fl::flow flow;
```

## see `src/test/main.cxx` for quick start example
It has a drag and move button.
