clear;
clc;
INITIAL = imread('A5.BMP');
tic;
EnterGarageFlag = 0;
JudgeBToWFlag = 0;
JudgeWToBFlag = 0;
BlackWhiteChangeCount = 0;
RecognizedCorrectLineCount = 0;

threshold = mean(INITIAL(:));
mt9v03x_image = INITIAL;
mt9v03x_image(mt9v03x_image < threshold) = 0;
mt9v03x_image(mt9v03x_image >= threshold) = 255;

for imageH=30:70
    BlackWhiteChangeCount = 0;
    for imageW=94:-1:40
        INITIAL(imageH,imageW) = 0;
        JudgeBToWFlag = 0;
        JudgeWToBFlag = 0;
        if mt9v03x_image(imageH,imageW)==0 && mt9v03x_image(imageH,imageW-1)==255
            for i=imageW-6:imageW-1
                if mt9v03x_image(imageH,i)==0
                     JudgeBToWFlag = 1;
                    break;
                end
            end
            if JudgeBToWFlag == 0
                for i=imageW:imageW+5
                    if mt9v03x_image(imageH,i)==255
                        JudgeBToWFlag = 1;
                        break;
                    end
                end
            end
            if JudgeBToWFlag == 0
                BlackWhiteChangeCount = BlackWhiteChangeCount + 1;
            end
        end
        if mt9v03x_image(imageH,imageW)==255 && mt9v03x_image(imageH,imageW-1)==0
            for i=imageW-6:imageW-1
                if mt9v03x_image(imageH,i)==255
                   JudgeWToBFlag = 1;
                   break;
                end
            end
            if JudgeWToBFlag == 0
                for i=imageW:imageW+5
                    if mt9v03x_image(imageH,i)==0
                       JudgeWToBFlag = 1;
                       break;
                    end
                end
            end
            if JudgeWToBFlag == 0
                BlackWhiteChangeCount = BlackWhiteChangeCount + 1;
            end
        end
    end
    for imageW=94:140
        INITIAL(imageH,imageW) = 0;
        JudgeBToWFlag = 0;
        JudgeWToBFlag = 0;
        if mt9v03x_image(imageH,imageW)==0 && mt9v03x_image(imageH,imageW+1)==255
            for i=imageW-5:imageW
                if mt9v03x_image(imageH,i)==255
                     JudgeBToWFlag = 1;
                    break;
                end
            end
            if JudgeBToWFlag == 0
                for i=imageW+1:imageW+6
                    if mt9v03x_image(imageH,i)==0
                        JudgeBToWFlag = 1;
                        break;
                    end
                end
            end
            if JudgeBToWFlag == 0
                BlackWhiteChangeCount = BlackWhiteChangeCount + 1;
            end
        end
        if mt9v03x_image(imageH,imageW)==255 && mt9v03x_image(imageH,imageW+1)==0
            for i=imageW-5:imageW
                if mt9v03x_image(imageH,i)==0
                   JudgeWToBFlag = 1;
                   break;
                end
            end
            if JudgeWToBFlag == 0
                for i=imageW+1:imageW+6
                    if mt9v03x_image(imageH,i)==255
                       JudgeWToBFlag = 1;
                       break;
                    end
                end
            end
            if JudgeWToBFlag == 0
                BlackWhiteChangeCount = BlackWhiteChangeCount + 1;
            end
        end
    end
    if BlackWhiteChangeCount >= 8
        RecognizedCorrectLineCount = RecognizedCorrectLineCount + 1;
    end
end

if RecognizedCorrectLineCount >= 5
		EnterGarageFlag = 1;
end
toc;

subplot(2,1,1);
imshow(INITIAL);
subplot(2,1,2);
imshow(mt9v03x_image);