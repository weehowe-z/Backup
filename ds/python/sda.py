import pygame,sys,os,random
pygame.init()
class rect():#����С��
    def __init__(self,filename,initial_position):
        self.image=pygame.image.load(filename)
        self.rect=self.image.get_rect()
        self.rect.topleft=initial_position
class goldrect(pygame.sprite.Sprite):#������
    def __init__(self,gold_position,speed):
        pygame.sprite.Sprite.__init__(self)
        self.image=pygame.image.load('image\\gold.png')
        self.rect=self.image.get_rect()
        self.rect.topleft=gold_position
        self.speed=speed
    def move(self):
        self.rect=self.rect.move(self.speed)
    def drawback(): #�������ͼƬ
        my_back=pygame.image.load('image\\qi3.jpg')
        bakscreen.blit(my_back,[0,0])
    def loadtext(levelnum,score,highscore):#����ɼ���level����߷ֵ�
        my_font=pygame.font.SysFont(None,24)
        levelstr='Level:'+str(levelnum)
        text_screen=my_font.render(levelstr, True, (255, 0, 0))
        bakscreen.blit(text_screen, (650,50))
        highscorestr='Higescore:'+str(highscore)
        text_screen=my_font.render(highscorestr, True, (255, 0, 0))
        bakscreen.blit(text_screen, (650,80))
        scorestr='Score:'+str(score)
        text_screen=my_font.render(scorestr, True, (255, 0, 0))
        bakscreen.blit(text_screen, (650,110))
    def loadgameover(scorenum,highscore):#���GAME OVER
        my_font=pygame.font.SysFont(None,50)
        levelstr='GAME OVER' over_screen=my_font.render(levelstr, True, (255, 0, 0))
        bakscreen.blit(over_screen, (300,240))
        highscorestr='YOUR SCORE IS'+str(scorenum)
        over_screen=my_font.render(highscorestr, True, (255, 0, 0))
        bakscreen.blit(over_screen, (280,290))
        if scorenum>int(highscore):#д����߷�
        highscorestr='YOUR HAVE GOT THE HIGHEST SCORE!'
        text_screen=my_font.render(highscorestr, True, (255, 0, 0))
        bakscreen.blit(text_screen, (100,340))
        highfile=open('highscore','w')
        highfile.writelines(str(scorenum))
        highfile.close()
    def gethighscore(): #��ȡ��߷�
        if os.path.isfile('highscore'):
            highfile=open('highscore','r')
            highscore=highfile.readline()
            highfile.close()
        else:
            highscore=0
        return highscore
bakscreen=pygame.display.set_mode([800,600])
bakscreen.fill([0,160,233])
pygame.display.set_caption('Dig!Dig!')
drawback()
levelnum=1 #level
scorenum=0 #�÷�
highscore=gethighscore()#��߷�
ileft=1 #��¼�����ƶ���������������ͼƬ
iright=10 #��¼�����ƶ���������������ͼƬ
x=100y=450filename='image\\1.png'backimg_ren=rect(filename,[x,y])
bakscreen.blit(backimg_ren.image,backimg_ren.rect)
loadtext(levelnum,scorenum,highscore)
goldx=random.randint(50,580)
speed=[0,levelnum]
mygold=goldrect([goldx,100],speed)
pygame.display.update()
while True:
if scorenum>0 and scorenum/50.0==int(scorenum/50.0):#���÷���50�ı���ʱ�޸�level
levelnum=scorenum/50+1 speed=[0,levelnum]
for event in pygame.event.get():
if event.type==pygame.QUIT:
sys.exit()
#make gold
pressed_keys= pygame.key.get_pressed()
if pressed_keys[pygame.K_LEFT]:#�������
drawback()
loadtext(levelnum,scorenum,highscore)
if iright > 14 :iright=10
iright=iright+1
filename='image\\'+str(iright)+'.png'
if x<50 :
x=50
else:
x=x-10
backimg_surface=rect(filename,[x,y])
bakscreen.blit(backimg_surface.image,backimg_surface.rect)
if pressed_keys[pygame.K_RIGHT]:#�����Ҽ�
drawback()
loadtext(levelnum,scorenum,highscore)
if ileft > 4 :ileft=0
ileft=ileft+1 filename='image\\'+str(ileft)+'.png'
if x>560:
x=560
else:
x=x+10
backimg_surface=rect(filename,[x,y])
bakscreen.blit(backimg_surface.image,backimg_surface.rect)
drawback()
loadtext(levelnum,scorenum,highscore)
mygold.move()
bakscreen.blit(mygold.image,mygold.rect)
backimg_surface=rect(filename,[x,y])
bakscreen.blit(backimg_surface.image,backimg_surface.rect)
if mygold.rect.top>600:#�жϽ���Ƿ��ŵأ�һ���ŵأ���Ϸ����
loadgameover(scorenum,highscore)
if mygold.rect.colliderect(backimg_surface.rect):#�жϽ���Ƿ���С����ײ�������ײ��ʾ
С�˽ӵ����
scorenum+=5 loadtext(levelnum,scorenum,highscore)
goldx=random.randint(50,580)
mygold=goldrect([goldx,100],speed)
pygame.display.update()
