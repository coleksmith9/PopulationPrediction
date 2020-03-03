from abc import ABCMeta,abstractmethod

class GivenNumbers(object):
    def debug() -> bool:
        rv=True;
        givenNumbers=GivenNumbers("debug/Inputs.txt")
        rv=(givenNumbers.get("One")==1)
        rv=(givenNumbers.get("Two")==2)
        rv=(givenNumbers.get("Three")==3)
        givenNumbers.set("One",10)
        givenNumbers.set("Four",4)
        rv=(givenNumbers.get("One")==10)
        rv=(givenNumbers.get("Four")==4)
        givenNumbers.set("One",1)
        givenNumbers.remove("Four")
        givenNumbers.save()
        givenNumbers=GivenNumbers("debug/Inputs.txt")
        rv=(givenNumbers.get("One")==1)
        rv=(givenNumbers.get("Two")==2)
        rv=(givenNumbers.get("Three")==3)
        return rv

    def __init__(self,filePath: str) -> None:
        self.__filePath=filePath
        self.__values=dict()
        self.__populateValues()

    def __populateValues(self) -> None:
        tempFile=open(self.__filePath,"r")
        for line in tempFile:
            parts=line.split('=')
            parts[1]=parts[1][0:len(parts[1])-1]
            self.__values[parts[0]]=float(parts[1])

    def get(self,numID: str) -> float:
        if (numID in self.__values):
            return self.__values[numID]
        return "ValNotInDict"

    def set(self,numID: str, num: float) -> None:
        self.__values[numID]=num

    def remove(self,numID: str) -> None:
        if (numID in self.__values):
            del self.__values[numID]

    def save(self) -> None:
        tempFile=open(self.__filePath,"w")
        for k,v in self.__values.items():
            tempFile.write("{0}={1}\n".format(k,v))


class ThreeDPair(object):
    def __init__(self) -> None:
        self.x=0
        self.y=0
        self.z=0

    def __init__(self,x: float, y: float,z: float) -> None:
        self.x=x
        self.y=y
        self.z=z


class UnsolvedDE(metaclass=ABCMeta):
    def debug() -> bool:
        rv=True
        #unsolvedDE=UnsolvedDE(GivenNumbers("debug/Inputs.txt"))
        #unsolvedDE.setIndependentVarInc(2)
        #unsolvedDE.setIV(100)
        #rv=(unsolvedDE.getIndependentVarInc()==2)
        #rv=(unsolvedDE.getIV()==100)
        return rv

    def __init__(self,constants):
        self.constants=constants
        self.__data=list()
        self.__initData()
        self.__independentVarInc=1

    def __initData() -> None:
        self.__data.append(ThreeDPair(0,0,0))

    def setIndependentVarInc(self,newInc: float) -> None:
        self.__independentVarInc=newInc

    def getIndependentVarInc(self) -> float:
        return self.__independentVarInc;

    def setIV(self,IV: float) -> None:
        self.__data[0].z=IV

    def getIV(self) -> float:
        return self.__data[0].z

    def incrementIndependentVar(self,val: float) -> None:
        threeDPoint=ThreeDPoint()
        threeDPoint.x=self.__data[len(self.__data)-1].x+self.__independentVarInc;
        threeDPoint.y=self.calculate();
        self.__data.append(threeDPoint)

    def calculateValue(self) -> None:
        threeDPoint.z=self.__data[len(self.__data)-2].z+self.__data[len(self.__data)-1].y

    @abstractmethod
    def calculate() -> float:
        raise NotImplementedError


class GrassUDE(UnsolvedDE):
    def __init__(self,prarieDogUDE):
        self.prarieDogUDE=prarieDogUDE

    def calcualte() -> float:
        return 0.0


class PrarieDogUDE(UnsolvedDE):
    def __init__(self,grassUDE):
        self.grassUDE=grassUDE

    def calcualte() -> float:
        return 0.0


def debug() -> None:
    rv=GivenNumbers.debug()
    rv&=UnsolvedDE.debug()
    print("Debug Successful: {0}".format(rv))


if __name__=="__main__":
    debug()
