# -*- coding:utf-8 -*-
#微信飞机大战，按Enter键开始，空格键暂停，游戏结束后按Enter键继续玩。
#第一次写游戏，希望大神勿喷，有建议和意见的可以给我评论。

# import libary
import pygame, random, sys, time
from pygame.locals import *

def terminate():
    pygame.quit()
    sys.exit()
    
def waitForPlayerToPressKey():
    while True:
        for event in pygame.event.get():
            if event.type == QUIT:
                terminate()
            if event.type == KEYDOWN:
                if event.key == K_ESCAPE: # pressing escape quits
                    terminate()
                if event.key == K_RETURN:
                    return

def playerHasHitSmallEnemy(playerRect, smallEnemy):
    for e in smallEnemy:
        erect = pygame.Rect(Smallone.get_rect())
        erect.top = e[1]
        erect.left = e[0]
        if playerRect.colliderect(erect):
            print 'small'
            return True
    return False

def playerHasHitMidEnemy(playerRect, MidEnemy):
    for e in MidEnemy:
        erect = pygame.Rect(Midone.get_rect())
        erect.top = e[1]
        erect.left = e[0]
        #print e[0],e[1],'h'
        if playerRect.colliderect(erect):
            print 'mid'
            return True
    return False

def playerHasHitBigEnemy(playerRect, BigEnemy):
    for e in BigEnemy:
        erect = pygame.Rect(Bigone.get_rect())
        erect.top = e[1]
        erect.left = e[0]
        if playerRect.colliderect(erect):
            print 'big'
            return True
    return False

def certainToPause():
    screen.blit(Start, (0, 0))
    pygame.display.update()
    while True:
        for e in pygame.event.get():
            if e.type == QUIT:
                terminate()
            if e.type == KEYDOWN:
                if e.key == K_SPACE:
                    return
            if e.type == KEYDOWN:
                if e.key == K_SPACE:
                    return

def drawText(text, font, surface, x, y):
    textobj = font.render(text, 1, ScoreColor)
    textrect = textobj.get_rect()
    textrect.topleft = (x, y)
    surface.blit(textobj, textrect)
    
# initialize the game
pygame.init()
WindowWidth, WindowHeight = 460, 680

# initate the music
pygame.mixer.init()

# set up fonts
font = pygame.font.SysFont(None, 48)
ScoreColor = (185, 122, 87)
ScoreFont = pygame.font.SysFont(None, 30)
#TEXTCOLOR = (0, 0, 0)
#RED = (255, 0, 0)

# set Window size
screen = pygame.display.set_mode((WindowWidth, WindowHeight))

# set window name
pygame.display.set_caption('Flight Game')

# load images
StartInterface = pygame.image.load("Resources/startone.png")
MainInterface = pygame.image.load("Resources/bg_02.png")
Plane = pygame.image.load("Resources/icon72x72.png")
Bullet = pygame.image.load("Resources/bullet.png")
Smallone = pygame.image.load("Resources/Smallone.png")
Midone = pygame.image.load("Resources/Middleone.PNG")
Bigone = pygame.image.load("Resources/Bigone.PNG")
Gameover = pygame.image.load("Resources/gameover.png")
Start = pygame.image.load("Resources/Start.PNG")

# load up music
Shoot = pygame.mixer.Sound("Resources/shoot.mp3")
Explosion = pygame.mixer.Sound("Resources/explosion.mp3")
Shoot.set_volume(0.05)
Explosion.set_volume(0.05)
pygame.mixer.music.load("Resources/main.mp3")

# show the "Start" screen
screen.blit(StartInterface, (0, 0))
pygame.display.update()
waitForPlayerToPressKey()

# keep looping through
while True:
    # set up the start parameter of the game (for restart)
    
    # record bullets
    bullets = [[0, 0]]
    # record the keys
    keys = [False,False,False,False]
    playerpos = [190, 610]
    smallenemy = [[100, 0]]
    midenemy = [[100, 0]]
    bigenemy = [[100, 0]]
    record = {'Bigone':0, 'Midone':0, 'Smallone':0}
    score = 0
    # wait event to pause
    Pause = False
    # time to update new enemy
    enemytimer = [100, 200, 400]
    enemytimers = [0, 0, 0]
    # time to update new bullet
    bullettime = 15

    pygame.mixer.music.play(-1, 0.0)
    pygame.mixer.music.set_volume(0.25)
    while True:
        i = 0
        for i in range(3):
            enemytimer[i] -= 1
        bullettime -= 1
        
        # clear the screen before drawing it again
        screen.fill(0)
        # draw the screen elements
        screen.blit(MainInterface, (0, 0))
        screen.blit(Plane, playerpos)

        # draw bullets
        if bullettime == 0:
            bullets.append([playerpos[0] + 32, playerpos[1]])
            bullettime = 15
        index = 0
        for bullet in bullets:
            if bullet[1] < 5:
                bullets.pop(index)
            bullet[1] -= 5
        for bullet in bullets:
            Shoot.play()
            screen.blit(Bullet, bullet)

        # draw smallenemy
        if enemytimer[0] == 0:
            smallenemy.append([random.randint(0, 430), 0])
            enemytimer[0] = 100 - (enemytimers[0] * 2)
            if enemytimers[0] >= 35:
                enemytimers[0] = 35
            else:
                enemytimers[0] += 5
        index = 0
        for enemy in smallenemy:
            if enemy[1] > 660:
                smallenemy.pop(index)
            enemy[1] += 2
            enemyrect = pygame.Rect(Smallone.get_rect())
            enemyrect.top = enemy[1]
            enemyrect.left = enemy[0]
            # check for collisions
            index1 = 0
            for bullet in bullets:
                bullrect = pygame.Rect(Bullet.get_rect())
                bullrect.top = bullet[1]
                bullrect.left = bullet[0]
                if enemyrect.colliderect(bullrect):
                    score += 1000 ###########################
                    Explosion.play()
                    bullets.pop(index1)
                    smallenemy.pop(index)
                index1 += 1 # delete index1 bullet
            index += 1 # delete index enemy
        for enemy in smallenemy:
            screen.blit(Smallone, enemy)

        # draw midenemy
        if enemytimer[1] == 0:
            midenemy.append([random.randint(0, 400), 0])
            enemytimer[1] = 200 - (enemytimers[1] * 2)
            if enemytimers[1] >= 35:
                enemytimers[1] = 35
            else:
                enemytimers[1] += 5
        index = 0
        for enemy in midenemy:
            if enemy[1] > 660:
                midenemy.pop(index)
            enemy[1] += 2
            enemyrect = pygame.Rect(Midone.get_rect())
            enemyrect.top = enemy[1]
            enemyrect.left = enemy[0]
            # check for collisions
            index1 = 0
            for bullet in bullets:
                bullrect = pygame.Rect(Bullet.get_rect())
                bullrect.top = bullet[1]
                bullrect.left = bullet[0]
                if enemyrect.colliderect(bullrect):
                    score += 6000 ###########################
                    Explosion.play()
                    bullets.pop(index1)
                    midenemy.pop(index)
                index1 += 1 # delete index1 bullet
            index += 1 # delete index enemy
        for enemy in midenemy:
            screen.blit(Midone, enemy)

        # draw Bigone
        if enemytimer[2] == 0:
            bigenemy.append([random.randint(0, 400), 0])
            enemytimer[2] = 400 - (enemytimers[2] * 2)
            if enemytimers[2] >= 35:
                enemytimers[2] = 35
            else:
                enemytimers[2] += 5
        index = 0
        for enemy in bigenemy:
            if enemy[1] > 660:
                bigenemy.pop(index)
            enemy[1] += 2
            enemyrect = pygame.Rect(Bigone.get_rect())
            enemyrect.top = enemy[1]
            enemyrect.left = enemy[0]
            # check for collisions
            index1 = 0
            for bullet in bullets:
                bullrect = pygame.Rect(Bullet.get_rect())
                bullrect.top = bullet[1]
                bullrect.left = bullet[0]
                if enemyrect.colliderect(bullrect):
                    score += 10000 ###########################
                    Explosion.play()
                    bullets.pop(index1)
                    bigenemy.pop(index)
                index1 += 1 # delete index1 bullet
            index += 1 # delete index enemy
        for enemy in bigenemy:
            screen.blit(Bigone, enemy)
        # display score
        drawText('score: %s' % (score), ScoreFont, screen, 90, 20)
        # update the screen
        pygame.display.flip()

        # loop through the events
        for event in pygame.event.get():
            # check if the event is the X button
            if event.type == pygame.QUIT:
                # if it is quit the game
                pygame.quit()
                exit(0)
            if event.type == pygame.KEYDOWN:
                if event.key==K_UP or event.key == K_w:
                    keys[0]=True
                elif event.key==K_LEFT or event.key == K_a:
                    keys[1]=True
                elif event.key==K_DOWN or event.key == K_s:
                    keys[2]=True
                elif event.key==K_RIGHT or event.key == K_d:
                    keys[3]=True
                elif event.key == K_SPACE:
                    certainToPause()           
            if event.type == pygame.KEYUP:
                if event.key==pygame.K_UP or event.key == K_w:
                    keys[0]=False
                elif event.key==pygame.K_LEFT or event.key == K_a:
                    keys[1]=False
                elif event.key==pygame.K_DOWN or event.key == K_s:
                    keys[2]=False
                elif event.key==pygame.K_RIGHT or event.key == K_d:
                    keys[3]=False
        # move player
        if keys[0] and playerpos[1] >= 10:
            playerpos[1] -= 5
        elif keys[2] and playerpos[1] <= 600:
            playerpos[1] += 5
        if keys[1] and playerpos[0] >= 0:
            playerpos[0] -= 5
        elif keys[3] and playerpos[0] <= 388:
            playerpos[0] += 5
        playerRect = Plane.get_rect()
        playerRect.top = playerpos[1]
        playerRect.left = playerpos[0]
        if playerHasHitSmallEnemy(playerRect, smallenemy) or playerHasHitMidEnemy(playerRect, midenemy) or playerHasHitMidEnemy(playerRect, bigenemy):
            pygame.mixer.music.stop()
            time.sleep(1)
            screen.blit(Gameover, (0, 0))
            drawText('%s' % (score), font, screen, 170, 400)
            pygame.display.update()
            waitForPlayerToPressKey()
            break
       
