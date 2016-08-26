// generated by Fast Light User Interface Designer (fluid) version 1.0303

#ifndef animataUI_h
#define animataUI_h
#include <FL/Fl.H>
class Fl_Eval_Slider;
#include <FL/Fl_Double_Window.H>
#include <stdlib.h>
#include "animata.h"
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Slider.H> /* Fl_Eval_Slider */
#include <math.h> /* Fl_Eval_Slider */
#include "Playback.h"
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_PNG_Image.H>
#include "ImageBox.h"
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Pack.H>
extern void cb_Create(Fl_Button*, long);
#include <vector>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Value_Input.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Dial.H>
extern void cb_Vertex(Fl_Check_Button*, long);
#include "Layer.h"
#include "FLU/Flu_Tree_Browser.h"
using namespace Animata;

class AnimataUI {
public:
  Playback *playback; 
  AnimataSettings settings; 
  AnimataUI();
  Fl_Double_Window *window;
private:
  inline void cb_window_i(Fl_Double_Window*, void*);
  static void cb_window(Fl_Double_Window*, void*);
  static Fl_Menu_Item menu_[];
  inline void cb_New_i(Fl_Menu_*, void*);
  static void cb_New(Fl_Menu_*, void*);
  inline void cb_Open_i(Fl_Menu_*, void*);
  static void cb_Open(Fl_Menu_*, void*);
  inline void cb_Import_i(Fl_Menu_*, void*);
  static void cb_Import(Fl_Menu_*, void*);
  inline void cb_Save_i(Fl_Menu_*, void*);
  static void cb_Save(Fl_Menu_*, void*);
  inline void cb_Save1_i(Fl_Menu_*, void*);
  static void cb_Save1(Fl_Menu_*, void*);
  inline void cb_Quit_i(Fl_Menu_*, void*);
  static void cb_Quit(Fl_Menu_*, void*);
  inline void cb_About_i(Fl_Menu_*, void*);
  static void cb_About(Fl_Menu_*, void*);
  Fl_Tabs *tabs;
  inline void cb_tabs_i(Fl_Tabs*, void*);
  static void cb_tabs(Fl_Tabs*, void*);
public:
  Fl_Group *imagePanel;
  Fl_Group *imageButtons;
private:
  inline void cb_Add_i(Fl_Button*, void*);
  static void cb_Add(Fl_Button*, void*);
  inline void cb_Move_i(Fl_Button*, long);
  static void cb_Move(Fl_Button*, long);
  inline void cb_Scale_i(Fl_Button*, long);
  static void cb_Scale(Fl_Button*, long);
public:
  Fl_Scroll *imageScrollArea;
  Fl_Pack *imagePack;
private:
  inline void cb_Create_i(Fl_Button*, long);
  static void cb_Create(Fl_Button*, long);
  inline void cb_Triangulate_i(Fl_Button*, void*);
  static void cb_Triangulate(Fl_Button*, void*);
  inline void cb_Texturize_i(Fl_Button*, long);
  static void cb_Texturize(Fl_Button*, long);
  inline void cb_threshold_i(Fl_Value_Slider*, void*);
  static void cb_threshold(Fl_Value_Slider*, void*);
public:
  Fl_Tabs *skeletonPrefTabs;
  Fl_Group *jointPrefs;
  Fl_Input *jointName;
private:
  inline void cb_jointName_i(Fl_Input*, void*);
  static void cb_jointName(Fl_Input*, void*);
public:
  Fl_Check_Button *jointOSC;
private:
  inline void cb_jointOSC_i(Fl_Check_Button*, void*);
  static void cb_jointOSC(Fl_Check_Button*, void*);
public:
  Fl_Value_Input *jointX;
private:
  inline void cb_jointX_i(Fl_Value_Input*, void*);
  static void cb_jointX(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *jointY;
private:
  inline void cb_jointY_i(Fl_Value_Input*, void*);
  static void cb_jointY(Fl_Value_Input*, void*);
public:
  Fl_Check_Button *jointFixed;
private:
  inline void cb_jointFixed_i(Fl_Check_Button*, void*);
  static void cb_jointFixed(Fl_Check_Button*, void*);
public:
  Fl_Group *bonePrefs;
  Fl_Input *boneName;
private:
  inline void cb_boneName_i(Fl_Input*, void*);
  static void cb_boneName(Fl_Input*, void*);
public:
  Fl_Eval_Slider *boneStiffness;
private:
  inline void cb_boneStiffness_i(Fl_Eval_Slider*, void*);
  static void cb_boneStiffness(Fl_Eval_Slider*, void*);
public:
  Fl_Value_Slider *boneLengthMult;
private:
  inline void cb_boneLengthMult_i(Fl_Value_Slider*, void*);
  static void cb_boneLengthMult(Fl_Value_Slider*, void*);
public:
  Fl_Value_Slider *boneLengthMultMin;
private:
  inline void cb_boneLengthMultMin_i(Fl_Value_Slider*, void*);
  static void cb_boneLengthMultMin(Fl_Value_Slider*, void*);
public:
  Fl_Value_Slider *boneLengthMultMax;
private:
  inline void cb_boneLengthMultMax_i(Fl_Value_Slider*, void*);
  static void cb_boneLengthMultMax(Fl_Value_Slider*, void*);
public:
  Fl_Value_Slider *boneTempo;
private:
  inline void cb_boneTempo_i(Fl_Value_Slider*, void*);
  static void cb_boneTempo(Fl_Value_Slider*, void*);
public:
  Fl_Group *attachVertices;
  Fl_Value_Slider *attachArea;
private:
  inline void cb_attachArea_i(Fl_Value_Slider*, void*);
  static void cb_attachArea(Fl_Value_Slider*, void*);
public:
  Fl_Value_Slider *attachFalloff;
private:
  inline void cb_attachFalloff_i(Fl_Value_Slider*, void*);
  static void cb_attachFalloff(Fl_Value_Slider*, void*);
  inline void cb_Attach_i(Fl_Button*, void*);
  static void cb_Attach(Fl_Button*, void*);
  inline void cb_Detach_i(Fl_Button*, void*);
  static void cb_Detach(Fl_Button*, void*);
public:
  Fl_Group *noPrefs;
private:
  inline void cb_play_i(Fl_Light_Button*, void*);
  static void cb_play(Fl_Light_Button*, void*);
  inline void cb_iteration_i(Fl_Value_Slider*, void*);
  static void cb_iteration(Fl_Value_Slider*, void*);
  inline void cb_gravity_i(Fl_Light_Button*, void*);
  static void cb_gravity(Fl_Light_Button*, void*);
  inline void cb__i(Fl_Value_Slider*, void*);
  static void cb_(Fl_Value_Slider*, void*);
  inline void cb_1_i(Fl_Dial*, void*);
  static void cb_1(Fl_Dial*, void*);
  inline void cb_Add1_i(Fl_Button*, void*);
  static void cb_Add1(Fl_Button*, void*);
  inline void cb_Delete_i(Fl_Button*, void*);
  static void cb_Delete(Fl_Button*, void*);
public:
  Fl_Input *layerName;
private:
  inline void cb_layerName_i(Fl_Input*, void*);
  static void cb_layerName(Fl_Input*, void*);
public:
  Fl_Value_Slider *layerAlpha;
private:
  inline void cb_layerAlpha_i(Fl_Value_Slider*, void*);
  static void cb_layerAlpha(Fl_Value_Slider*, void*);
public:
  Fl_Check_Button *layerVisible;
private:
  inline void cb_layerVisible_i(Fl_Check_Button*, long);
  static void cb_layerVisible(Fl_Check_Button*, long);
public:
  Fl_Value_Input *layerPositionX;
private:
  inline void cb_layerPositionX_i(Fl_Value_Input*, void*);
  static void cb_layerPositionX(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *layerPositionY;
private:
  inline void cb_layerPositionY_i(Fl_Value_Input*, void*);
  static void cb_layerPositionY(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *layerDepth;
private:
  inline void cb_layerDepth_i(Fl_Value_Input*, void*);
  static void cb_layerDepth(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *layerScale;
private:
  inline void cb_layerScale_i(Fl_Value_Input*, void*);
  static void cb_layerScale(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *layerRotationX;
private:
  inline void cb_layerRotationX_i(Fl_Value_Input*, void*);
  static void cb_layerRotationX(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *layerRotationY;
private:
  inline void cb_layerRotationY_i(Fl_Value_Input*, void*);
  static void cb_layerRotationY(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *layerRotationZ;
private:
  inline void cb_layerRotationZ_i(Fl_Value_Input*, void*);
  static void cb_layerRotationZ(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *layerOffsetX;
private:
  inline void cb_layerOffsetX_i(Fl_Value_Input*, void*);
  static void cb_layerOffsetX(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *layerOffsetY;
private:
  inline void cb_layerOffsetY_i(Fl_Value_Input*, void*);
  static void cb_layerOffsetY(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *layerOffsetZ;
private:
  inline void cb_layerOffsetZ_i(Fl_Value_Input*, void*);
  static void cb_layerOffsetZ(Fl_Value_Input*, void*);
public:
  Fl_Check_Button *playback_show_hide;
private:
  inline void cb_playback_show_hide_i(Fl_Check_Button*, void*);
  static void cb_playback_show_hide(Fl_Check_Button*, void*);
  inline void cb_Vertex_i(Fl_Check_Button*, long);
  static void cb_Vertex(Fl_Check_Button*, long);
public:
  AnimataWindow *editorBox;
private:
  Fl_Group *layers;
public:
  Flu_Tree_Browser *layerTree;
private:
  inline void cb_layerTree_i(Flu_Tree_Browser*, void*);
  static void cb_layerTree(Flu_Tree_Browser*, void*);
  Fl_Group *extra_includes_etc;
public:
  void show();
  void fullscreen();
  void resize(int x, int y, int w, int h);
  ImageBox * loadImage(const char *filename);
  ~AnimataUI();
  Fl_File_Chooser *fileChooser; 
  void refreshLayerTree(Layer *root);
  void clearLayerTree();
private:
  void addLayerNodeRecursive(Layer *layer, Flu_Tree_Browser::Node *node);
  union { int i; float f; const char *str; } tempStorage /* temporary storage space for returning values as void * */; 
};

class Fl_Eval_Slider : public Fl_Slider {
  uchar textfont_, textsize_; 
  unsigned textcolor_; 
public:
  Fl_Eval_Slider(int X, int Y, int W, int H, const char *L) ;
  void draw();
  int handle(int event);
  Fl_Font textfont() const;
  void textfont(uchar s);
  uchar textsize() const;
  void textsize(uchar s);
  Fl_Color textcolor() const;
  void textcolor(unsigned s);
private:
  float eval(float f);
  float evalinv(float f);
public:
  float value();
  void value(float f);
};
#endif
