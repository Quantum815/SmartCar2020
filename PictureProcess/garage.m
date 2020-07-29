clear;
clc;
INITIAL = imread('test1.BMP');

EnterGarageFlag = 0;
JudgeFlag = 0;
BlackWhiteChangeCount = 0;
RecognizedCorrectLineCount = 0;

threshold = mean(INITIAL(:));
mt9v03x_image = INITIAL;
mt9v03x_image(mt9v03x_image < threshold) = 0;
mt9v03x_image(mt9v03x_image >= threshold) = 255;

for imageH=60:85
    for imageRW=94:-1:60
        for imageLW=93:-1:59
            JudgeFlag = 0;
            if mt9v03x_image(imageH,imageRW)==0 && mt9v03x_image(imageH,imageLW)==255
                for i=imageLW-5:imageLW
                    if mt9v03x_image(imageH,i)==0
                        JudgeFlag = 1;
                    end
                end
                for i=imageRW+5:-1:imageRW
                    if mt9v03x_image(imageH,i)==255
                        JudgeFlag = 1;
                    end
                end
                if JudgeFlag == 1
                    continue;
                else
                    BlackWhiteChangeCount = BlackWhiteChangeCount + 1;
                    RecognizedCorrectLineCount = RecognizedCorrectLineCount + 1;
                end
            end
            if mt9v03x_image(imageH,imageRW)==255 && mt9v03x_image(imageH,imageLW)==0
                for i=imageLW-5:imageLW
                    if mt9v03x_image(imageH,i)==255
                        JudgeFlag = 1;
                    end
                end
                for i=imageRW+5:-1:imageRW
                    if mt9v03x_image(imageH,i)==0
                        JudgeFlag = 1;
                    end
                end
                if JudgeFlag == 1
                    continue;
                else
                    BlackWhiteChangeCount = BlackWhiteChangeCount + 1;
                    RecognizedCorrectLineCount = RecognizedCorrectLineCount + 1;
                end
            end
        end
    end
    for imageLW=94:130 
        for imageRW=95:131
            JudgeFlag = 0;
            if mt9v03x_image(imageH,imageRW)==0 && mt9v03x_image(imageH,imageLW)==255
                for i=imageLW-5:imageLW
                    if mt9v03x_image(imageH,i)==0
                        JudgeFlag = 1;
                    end
                end
                for i=imageRW+5:-1:imageRW
                    if mt9v03x_image(imageH,i)==255
                        JudgeFlag = 1;
                    end
                end
                if JudgeFlag == 1
                    continue;
                else
                    BlackWhiteChangeCount = BlackWhiteChangeCount + 1;
                    RecognizedCorrectLineCount = RecognizedCorrectLineCount + 1;
                end
            end
            if mt9v03x_image(imageH,imageRW)==255 && mt9v03x_image(imageH,imageLW)==0
                for i=imageLW-5:imageLW
                    if mt9v03x_image(imageH,i)==255
                        JudgeFlag = 1;
                    end
                end
                for i=imageRW+5:-1:imageRW
                    if mt9v03x_image(imageH,i)==0
                        JudgeFlag = 1;
                    end
                end
                if JudgeFlag == 1
                    continue;
                else
                    BlackWhiteChangeCount = BlackWhiteChangeCount + 1;
                    RecognizedCorrectLineCount = RecognizedCorrectLineCount + 1;
                end
            end
        end
    end
end

if(BlackWhiteChangeCount >= 4 && RecognizedCorrectLineCount >= 4)
		EnterGarageFlag = 1;
end

subplot(2,1,1);
imshow(INITIAL);
subplot(2,1,2);
imshow(mt9v03x_image);
fprintf("threshold = %f EnterGarageFlag = %d\n", threshold, EnterGarageFlag);