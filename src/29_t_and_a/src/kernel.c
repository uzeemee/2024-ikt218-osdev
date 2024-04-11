#include <multiboot2.h>
#include "libc/stdint.h"
#include "libc/stddef.h"
#include "libc/stdbool.h"
#include "libc/stdarg.h"
#include "memory/memory.h"
#include "vga/vga.h"
#include "gdt/gdt.h"
#include "pit/timer.h"

//#include "idt/idt.h"
//#include "pit/pit.h"
//#include "irq/irq.h"
//#include "memory/memory.h"

extern uint32_t end;

struct multiboot_info {
    uint32_t size;
    uint32_t reserved;
    struct multiboot_tag *first;
};

int kernel_main();


void enter_protected_mode() {
    asm volatile (
        "mov %cr0, %eax\n\t"
        "or $0x1, %eax\n\t"
        "mov %eax, %cr0\n\t"
    );
}


void do_sum(){
    printf("Hello");
    printf("Hello");
    printf("Hello");
    printf("Hello");
    printf("Hello");
    printf("Hello");
    printf("Hello");
}

void clear_screen() {
    volatile char *video = (volatile char*)0xB8000;
    
    // Loop through each character cell on the screen
    for (int i = 0; i < 80 * 25; ++i) {
        // Set each character cell to space (' ') and black background color
        *video++ = ' ';
        *video++ = 0x0;
    }
}



void boot_screen(){
    clear_screen();
    Reset();
    printf("Loading...");for (int i = 0; i < 80; i++){
         sleep(10);
        //printf("Done %d", counter++);
        print("|");
        
    }
    clear_screen();
    Reset();
    printf("Booting complete!");
    sleep(500);
    clear_screen();
    Reset();

    const char *welcome[] = {
"""ine#finine#define/**/Alan/**/(fflush(0),j=c=0;++c<b[6]+7;v=b[c]^(b[c+^(+^b[c+^cc""",
"""*H=cr*H*H=char*H='close/r//nContent-Type:text/html/r/n/r/n<canvasid=/as/aid=/a=n""",
"""idt'wididt'c'width='128'height='128'style='width:256px;height:256px'/56/5px'/5':""",
"""rip>cririp><script>x=y=-1;v=window.c;v.onmousemove=function(e){x=e.p/x=/xe.p/xp)""",
"""-v.aX-v-v.ageX-v.offsetLeft;y=e.               pageY-v.offsetTop};w=/p}/p;w=/p=T""",
"""Webn WeWebnew WebSocket('ws'+                     location.href.subs/.s/.ubs/.se""",
"""));t4))));tr(4));w.binarya                          pType='arraybuff/yb/yuff/yfr""",
"""w.oe;w.w.oer';w.onmessq                               kage=function(/ti/ton(/t(n""",
"""=v.ec=v=v.e){c=v.getCs                                 qontext('2d')/'2/'d')/')t""",
""".cr;c.c.cr;b=c.creaa              ptea                 lmpageData(12/ta/t(12/t2D""",
"""8);828)8);8,128);u=        new Uint8Array(d=e.           data);b.dat/b./bdat/bt)""",
"""t(uaet(t(ua.set(u)      ;c.putImageData(b,0,0)            ;u[0]=x/2;/=x/=/2;/=;0""",
"""=y/u]=y=y/u[1]=y/2    ;w.send(d.slice(0,x<0?0:             2));x=y=-/x=/xy=-/x-)""",
"""scr1/scscr1}</scr'   'ipt>',b[9999];float*e,d[             65536],u,v6]v6,u,v6,5""",
"""lv,,,lvlv,,lu,lv,    z;void*f;typedef unsigned              long longg gglonggno""",
"""p,tl*p,p,tl;l*p,t[  99]={0x67452301,0xEFCDAB89,            0x98BADCFEBAEBDCFEBF9""",
"""438,843438,308438*  881,3285377520       },i,j,k           ,n,m[204];[2;[04];[],""",
"""lud#clulud#include        /*io*/          <stdio.h>        /*turing*/ri/rng*/r*t""",
""" s(vd s s(void s(){  ;     for(  k          =0;k++<7 *  2  *9;)for(i=fo=fr(i=fi;""",
"""i<10+i<i<10;++i<127; )      e=d +  i* 4   +512*k,1[e]      +=(i-u)*(i-ui-)*(i-((""",
"""(k--+(k(k--u)+(k-v)* (k- v  )<20?*e+=UV_DROP:0;}l*q=  m,   g=1LL<<32;L<;L<32;L21""",
"""(l l)(l(l l(h)(l v,l (a)){ return(v<<a)|(v/g>>(32-a    )  );}int maint ntmaintii""",
""" c/(t c c/(int c/*ha r*/,  char**y){for(e=d;fgets(b      ,m[97]=480,#=4#=80,#=,7""",
"""n&&sin&n&&stdin&&*b >31;  for( i=j=0;n=b[i],i<18   ?  (l) sec--webs//we/wbs//w/-""",
"""t-koet-t-kocket-key: '[i]       ==(n|32):n-32? m[j/4]  |=(j< 24?n:(l)?n)?:(l)?l2""",
"""EAF'8EAEAF'258EAFA5-  E914-47DA-95CA-C5AB0DC85B        11//x80[j-24])j-)j24])j]0""",
"""-j/<3-j-j/<<(3-j/4)*8 ,++j<61:1;)i++;for(j=3;--j;    ){for(i=4;++i<74++4+i<74+74""",
"""9?p;>9?9?p;)i>9?p=q+i- 2             ,p[8]=h(p[5     ]^*p^p[-6]^p[-8]^p]^[-8]^86""",
"""ine#finine#define/*hah  aha          <--mouth*/      laplacian(u)l##uu)uul##uu#n""",
"""(t[,:(t(t[,1):(t[i]=t[9 -i]       );for(p=t+7          ,i=-1;++i<82;ki<ki82;ki;+""",
"""+,p=++,+,p=*p++,p[2]=h(p[1],5)   +p[-3]+n+     (i/+     20/2?*p^k^p[-^k-^^p[-^[*""",
"""*p&2(*p*p&2]:(*p&k)|((i< 20?~*p:*p|k)&p       [-2        ]))+*q++,t[+++++,t[++[*""",
"""]+=8i]+]+=81-i]+=(i>76)*     (* p=          h(*           p,30*(i<80)(i)(<80)(00""",
"""or()foror()))for(;n-k;n=(((               1LL               +(9<<i/20<<0<i/20<2(""",
"""<<6))<<<<6)/8)<<60)/k+k)/2)             k=n   ;}  for     (i =0;i<57;;i;;<57;;7=""",
"""i<3i)i<i<3i++)i<30?q[i/5*             16/   3+   i/5]   |=t[i/5]/g<<4]/4]g<<4]</""",
"""0+i>30+0+i>>(30+i/5/3*2-i/5       *6)&   63,0    :(n   =*q++,b[i-30]=i-=i30]=i]b""",
"""?n-n2?n?n-n<62?n-37+//fl     [n      /26]:n    *4-    205);)for(prin/(p/(rin/(no""",
"""TTPtHTTTTPtf/HTTP/1.1 /*    |     *///d             OK//r//nConnecti/ne/ncti/nio""",
"""s/.o/s/s/.on:/s/.27s=/r/n/r/n       ,101   +99*!  *m,!*m?H: /upgrade/gr/gade/geu""",
"""Upg/nUpUpg/r/nUpgrade:websop        acl   pket/r/nSec-WebSocket-Acce/-A/-cce/-ee""",
""",b)p ,b,b)pt: ,b);e-d<65536 ;      e+=  4)e[1]=(*e=UV_BACKGROUND);forD)rD;forDoU""",
"""c=0(;c=c=0(;m;c=0)/{for(f= c<      2   ?0:fopen(y[1],'r);f&&fscanf(f,an,af(f,afs""",
"""f, //f,f, /f,/f, ,&u,&v/>0;)s      ();for(;j<SPEED*4;j+=2)for(i=0;i</=0/=;i</=<(""",
"""4;e604;4;e63504;e+=5-j/4*2,z=      TIMESTEP,*e=u+z*(elta_u),e[1]=v+z*]=*]v+z*]z[""",
"""a_v(ta_a_v(elta_v),i+=4)for(c=  0;c+2;u=v,v=e[4],lu=lv,lv=e[-508]+*e+8]+8+*e+8e5""",
"""+e[e]+e+e[e[8]+e[516]-v*4)e=d+i+512+i/504*8+j/4-c--;for(;n=c/4,65544>65>6544>644""",
"""+)pc++)+)pc;c++)putchar(c>7?n>2||(u=d[c-n-7]*4*(n<2?!n?RGB))>255?255:5?:5255:552""",
"""ine#finine#define/*x*/Turing(x)4]=getchar()&127))u=v;if(b[6]>1)s();}}s(}s);}}s}1""",
"""0:uu?0:0:uu<0?0:u:c<0?124-c*3:c==5);/* -- The word /genius  is */ for*/r* for*os"""};


    const int delay_ms = 20; // Delay in microseconds (0.5 second)


    for (int i = 0; i < 49; i++) {
        print("%s\n", welcome[i]);
        sleep(delay_ms);
    }
    printf("\n\n\n");
    //sleep(delay_ms);
    for (int i = 0; i < 30; i++) {
        printf("\033[A\033[K"); // Move cursor up and clear line
        sleep(delay_ms);        // Delay between frames
    }
    clear_screen();
    Reset();
    printf("Welcome.\n");

}



int main(uint32_t magic, struct multiboot_info* mb_info_addr) {
    init_gdt();
    init_idt();
    init_irq();
    init_pit();
    //init_kernel_memory(&end);
    //init_paging();
    //print_memory_layout();
    
    //init_timer(1000);
    //printf("Loading...");
    //asm volatile ("int $0x08");
    //asm volatile ("int $0x10");
    //asm volatile ("int $0x11");
    //asm volatile ("int $0x12");
    //asm volatile ("int $0x13");
    //asm volatile ("int $0x14");

    // /*When I activate this the scroll is messed up*/
    asm volatile ("int $0x00");
    asm volatile ("int $0x01");
    asm volatile ("int $0x02");
    asm volatile ("int $0x03");
    asm volatile ("int $0x04");
    asm volatile ("int $0x05");
    asm volatile ("int $0x06");
    asm volatile ("int $0x07");
    asm volatile ("int $0x09");
    asm volatile ("int $0x0F");  // Interrupt 15
    asm volatile ("int $0x10");  // Interrupt 16
    asm volatile ("int $0x11");  // Interrupt 17
    asm volatile ("int $0x12");  // Interrupt 18
    asm volatile ("int $0x20");
    ////asm volatile ("sti");
    sleep(1000);
    //int a = 0/0;
    //int counter = 0;
    //asm volatile("sti");
    //sleep(10);
    printf("Booting...");


    boot_screen();
    //printf("We Moving!");
    return kernel_main();
}