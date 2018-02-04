#include<graphics.h>
#include<stdio.h>
#include<conio.h>
#include<dos.h>

union REGS i,o;
int leftcolor[15];

//function to initialize mouse pointer
int initmouse()
{
 i.x.ax=0;
 int86(0X33,&i,&o);
 return(o.x.ax);
}

//function to show mouse pointer
void showmouseptr()
{
 i.x.ax=1;
 int86(0x33,&i,&o);
}

//function to hide mouse pointer
void hidemouseptr()
{
 i.x.ax=2;
 int86(0X33,&i,&o);
}

//function to restrict mouse pointer in given domain
void restrictmouseptr(int x1,int y1,int x2,int y2)
{
 i.x.ax=7;
 i.x.cx=x1;
 i.x.dx=x2;
 int86(0x33,&i,&o);
 i.x.ax=8;
 i.x.cx=y1;
 i.x.dx=y2;
 int86(0x33,&i,&o);
}

//function to get current position of mouse
void getmousepos(int *button,int *x,int *y)
{
 i.x.ax=3;
 int86(0x33,&i,&o);
 *button=o.x.bx;
 *x=o.x.cx;
 *y=o.x.dx;
}

// function to draw layout of the application
void draw_tool_box()
{
  int maxx,maxy,right=43,i;
  maxx=getmaxx();                   //function to get max pixel in x
  maxy=getmaxy();                   //function to get max pixel in y
  
  line(0,18,maxx,18);	             //horizontal line below PAINT
  line(0,maxy-36,maxx,maxy-36);    //horizontal line for color panel
  line(0,maxy-18,maxx,maxy-18);  //horizontal line for press any key to exit
  line(620,0,620,18);         //vertical line for "X"
  line(602,0,602,18);         //vertical line for "R"
  line(584,0,584,18);         //vertical linr for "-"

  outtextxy(301,6,"PAINT");
  outtextxy(275,maxy-12,"PRESS ANY KEY TO EXIT.....");
  outtextxy(589,6,"-");
  outtextxy(607,6,"R");
  outtextxy(625,6,"X");
  
  line(30,18,30,maxy-36);      //vertical line of tool box
  
  for(i=0;i<16;i++)            //loop to draw vertical lines in tool box
  {
   line(0,right,30,right);
   right+=25;
  }
  
  rectangle(7,25,23,35);
  ellipse(15,55,0,360,10,5);
  circle(15,80,8);
  line(10,98,20,113);
  bar(7,125,23,135);
  fillellipse(15,155,10,5);
  outtextxy(10,178,"F");
  outtextxy(10,202,"E");
  outtextxy(2,228,"PXL");
  outtextxy(10,202,"E");
  outtextxy(10,202,"E");
  outtextxy(10,202,"E");
  outtextxy(10,202,"E");
  outtextxy(10,202,"E");
  outtextxy(10,202,"E");
  outtextxy(5,402,"CLR");
  outtextxy(35,maxy-30,"COLOR PANEL->");
}

//function to draw color panel
void color_panel()
{
  int left,top,c,color;
  left=175;
  top=445;
  
  for(c=1;c<=15;c++)                //loop to draw color bars
  {
   setfillstyle(SOLID_FILL,c);
   bar(left,top,left+12,top+12);
   leftcolor[c-1]=left;
   left+=26;
  }
}

//function to change color
void change_color(int x,int y)
{
 int c;
 for(c=0;c<=13;c++)
 {
  if(x>leftcolor[c]&&x<(leftcolor[c+1]-12)&&y>445&&y<457)
  {
   setcolor(c+1);
   setfillstyle(SOLID_FILL,c+1);
   bar(7,425,23,435);                        //bar to represent current color
  }
  if(x>leftcolor[14]&&x<565&&y>445&&y<457)
  {
   setcolor(WHITE);
   setfillstyle(SOLID_FILL,WHITE);
   bar(7,435,23,445);                        //bar to represent current color
  }
 }
}

//function to select shape
int select_shape(int x,int y)
{
  if(x>0&&x<30&&y>18&&y<43)
  return 1;
  else if(x>0&&x<30&&y>43&&y<68)
  return 2;
  else if(x>0&&x<30&&y>68&&y<93)
  return 3;
  else if(x>0&&x<30&&y>93&&y<118)
  return 4;
  else if(x>0&&x<30&&y>118&&y<143)
  return 5;
  else if(x>0&&x<30&&y>143&&y<168)
  return 6;
  else if(x>0&&x<30&&y>168&&y<193)
  return 7;
  else if(x>0&&x<30&&y>193&&y<218)
  return 8;
  else if(x>0&&x<30&&y>218&&y<243)
  return 9;
  else if(x>0&&x<30&&y>243&&y<268)
  return 10;
  else if(x>0&&x<30&&y>268&&y<293)
  return 11;
  else if(x>0&&x<30&&y>293&&y<318)
  return 12;
  else if(x>0&&x<30&&y>318&&y<343)
  return 13;
  else if(x>0&&x<30&&y>343&&y<368)
  return 14;
  else if(x>0&&x<30&&y>368&&y<393)
  return 15;
  else if(x>0&&x<30&&y>393&&y<418)
  return 16;
  else
  return 0;
}

// driver function for the application
void main()
{
 int gd=DETECT,gm,maxx,maxy,x,y,button,flag,temp1,temp2,color;
 initgraph(&gd,&gm,"c:\\tc\\bgi");
 
 maxx=getmaxx();
 maxy=getmaxy();
 
 rectangle(0,0,maxx,maxy);
 setviewport(0,0,maxx-1,maxy-1,1);
 
 draw_tool_box();
 color_panel();
 initmouse();
 showmouseptr();
 restrictmouseptr(1,1,maxx-1,maxy-1);
 flag=7;
 setviewport(31,19,maxx-1,maxy-37,1);
 
 while(!kbhit())
 {
  getmousepos(&button,&x,&y);
  if(button==1)
  {
    if(x>0&&x<635&&y>442&&y<460)
    change_color(x,y);
    else if(x>0&&x<30&&y>18&&y<maxy-36)
    flag=select_shape(x,y);
    temp1=x-31;
    temp2=y-19;

    if(flag==7)
    {
     hidemouseptr();
     while(button==1)
     {
      line(temp1,temp2,x-31,y-19);
      temp1=x-31;
      temp2=y-19;
      getmousepos(&button,&x,&y);
     }
     showmouseptr();
    }
    else if(flag==8)
     {
       color=getcolor();
       hidemouseptr();
       while(button==1)
       {
       setcolor(BLACK);
       line(temp1,temp2,x-31,y-19);
       temp1=x-31;
       temp2=y-19;
       getmousepos(&button,&x,&y);
       }
       showmouseptr();
       setcolor(color);
     }

    while(button==1)

     getmousepos(&button,&x,&y);
     hidemouseptr();

     if(flag==1)
     rectangle(temp1,temp2,x-31,y-19);
     else if(flag==2)
     ellipse(temp1,temp2,0,360,x-31-temp1,y-19-temp2);
     else if(flag==3)
     circle(temp1,temp2,x-31-temp1);
     else if(flag==4)
     line(temp1,temp2,x-31,y-19);
     else if(flag==5)
     {
      setfillstyle(SOLID_FILL,getcolor());
      bar(temp1,temp2,x-31,y-19);
     }
     else if(flag==6)
     fillellipse(temp1,temp2,x-31-temp1,y-19-temp2);
     else if(flag==9)
     putpixel(x-31,y-19,getcolor());
     //else if(flag==10)
     //else if(flag==11)
     //else if(flag==12)
     //else if(flag==13)
     //else if(flag==14)
     //else if(flag==15)
     else if(flag==16)
     {
      flag=7;
      clearviewport();
     }
     showmouseptr();
   }


 }
closegraph();
}