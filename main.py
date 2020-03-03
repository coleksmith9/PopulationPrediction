import os.path
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
        tempFile.close()

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
        tempFile.close()


class TwoDPair(object):
    def __init__(self, x: float=0, y: float=0) -> None:
        self.x=x
        self.y=y


class ThreeDPair(object):
    def __init__(self,x: float=0, y: float=0,z: float=0) -> None:
        self.x=x
        self.y=y
        self.z=z


class UnsolvedDE(metaclass=ABCMeta):
    def debug() -> bool:
        return True

    def __init__(self,constants):
        self.constants=constants
        self.__data=list()
        self.__initData()
        self.__independentVarInc=1

    def __initData(self) -> None:
        self.__data.append(ThreeDPair(0,0,0))

    def setIndependentVarInc(self,newInc: float) -> None:
        self.__independentVarInc=newInc

    def getIndependentVarInc(self) -> float:
        return self.__independentVarInc;

    def setIV(self,IV: float) -> None:
        self.__data[0].z=IV

    def getIV(self) -> float:
        return self.__data[0].z

    def getIndependentVar(self) -> float:
        return self.__data[len(self.__data)-1].x

    def getDependentVar(self) -> float:
        return self.__data[len(self.__data)-2].z

    def getDataPoint(self):
        return TwoDPair(self.__data[len(self.__data)-1].x,self.__data[len(self.__data)-1].z)

    def incrementIndependentVar(self) -> None:
        threeDPair=ThreeDPair()
        threeDPair.x=self.__data[len(self.__data)-1].x+self.__independentVarInc;
        threeDPair.y=self.calculate();
        self.__data.append(threeDPair)

    def calculateValue(self) -> None:
        self.__data[len(self.__data)-1].z=self.__data[len(self.__data)-2].z+self.__data[len(self.__data)-1].y

    @abstractmethod
    def calculate(self) -> float:
        raise NotImplementedError


class GrassUDE(UnsolvedDE):
    def debug() -> bool:
        rv=True
        constants=GivenNumbers("debug/Inputs.txt")
        grassUDE=GrassUDE(constants)
        grassUDE.setIndependentVarInc(2)
        grassUDE.setIV(100)
        rv=(grassUDE.getIndependentVarInc()==2)
        rv=(grassUDE.getIV()==100)
        return rv

    def __init__(self,constants,prarieDogUDE=None):
        super(GrassUDE,self).__init__(constants)
        self.setPrarieDogUDE(prarieDogUDE)

    def setPrarieDogUDE(self,prarieDogUDE):
        self.prarieDogUDE=prarieDogUDE

    def calculate(self) -> float:
        popGrowth=self.constants.get("GrassGrowthRate")*self.getDependentVar()
        popDecline=self.constants.get("GrassEaten")*self.getDependentVar()*self.prarieDogUDE.getDependentVar()
        return popGrowth-popDecline


class PrarieDogUDE(UnsolvedDE):
    def debug() -> bool:
        rv=True
        constants=GivenNumbers("debug/Inputs.txt")
        prarieDogUDE=PrarieDogUDE(constants)
        prarieDogUDE.setIndependentVarInc(2)
        prarieDogUDE.setIV(100)
        rv=(prarieDogUDE.getIndependentVarInc()==2)
        rv=(prarieDogUDE.getIV()==100)
        return rv

    def __init__(self,constants,grassUDE=None):
        super(PrarieDogUDE,self).__init__(constants)
        self.setGrassUDE(grassUDE)

    def setGrassUDE(self,grassUDE):
        self.grassUDE=grassUDE

    def calculate(self) -> float:
        popGrowth=self.constants.get("PrarieDogGrowthRate")*self.getDependentVar()*self.grassUDE.getDependentVar()
        popDecline=self.constants.get("PrarieDogDeathRate")*self.getDependentVar()
        return popGrowth-popDecline


class CSVFile(object):
    def debug() -> bool:
        rv=True
        csvFile=CSVFile("debug/CSVTest.csv")
        rv=(csvFile.getDataRow(0)[0]=="1")
        rv=(csvFile.getDataRow(1)[0]=="5")
        rv=(csvFile.getDataRow(2)[0]=="1")
        rv=(len(csvFile.getDataRow(3))==0)
        rv=(csvFile.lookupDataRow("5")[2]=="7")
        csvFile.write()
        return rv

    def __init__(self, filePath: str) -> None:
        self.__filePath=filePath
        self.__headers=list()
        self.__data=list()
        self.read()

    def addHeader(self,header: str) -> None:
        self.__headers.append(header)

    def addDataRow(self,dataList: list) -> None:
        self.__data.append(dataList)

    def read(self,filePath=None) -> None:
        if (filePath!=None):
            self.write()
            self.clear()
            self.__filePath=filePath
        if os.path.exists(self.__filePath):
            tempFile=open(self.__filePath,"r")
            self.__headers=tempFile.readline().rstrip("\r\n").split(',')
            for line in tempFile:
                self.addDataRow(line.rstrip("\r\n").split(','))
            tempFile.close()
        #print(self.__headers)
        #print(self.__data)

    def getDataRow(self, index: int) -> list:
        if (index<len(self.__data)):
            return self.__data[index]
        return list()

    def lookupDataRow(self, val: str) -> list:
        rv=list()
        for i in range(0,len(self.__data)):
            rv=self.getDataRow(i)
            if rv[0]==val:
                break
        return rv
    
    def write(self) -> None:
        tempFile=open(self.__filePath,"w")
        for i in range(0,len(self.__headers)):
            tempFile.write(self.__headers[i])
            if i!=len(self.__headers)-1:
                tempFile.write(',')
            else:
                tempFile.write('\n')
        for x in self.__data:
            for i in range(0,len(x)):
                tempFile.write("{0}".format(x[i]))
                if i!=len(x)-1:
                    tempFile.write(',')
                else:
                    tempFile.write('\n')
        tempFile.close()

    def clear(self) -> None:
        self.__data=list()

    def clearHeaders(self) -> None:
        self.__headers=list()


class Simulation(object):
    def debug() -> bool:
        rv=True
        sim=Simulation(GivenNumbers("debug/Inputs.txt"))
        sim.setResultsFile("debug/Results.txt")
        sim.run()
        threeDPoint=sim.getDataPoint(10)
        rv=(threeDPoint.x==0)
        rv=(threeDPoint.y==0)
        rv=(threeDPoint.z==0)
        sim.save()
        return rv

    def __init__(self,constants) -> None:
        self.__constants=constants
        self.__grassUDE=None
        self.__prarieDogUDE=None
        self.__csvFile=None
        self.__setupCSVFile()
        self.setup()

    def __setupCSVFile(self) -> None:
        self.__csvFile=CSVFile("data/results.csv")
        self.__csvFile.addHeader("Time")
        self.__csvFile.addHeader("GrassPopulation")
        self.__csvFile.addHeader("PrarieDogPopulation")

    def setup(self) -> None:
        self.__grassUDE=GrassUDE(self.__constants)
        self.__prarieDogUDE=PrarieDogUDE(self.__constants)

        self.__prarieDogUDE.setGrassUDE(self.__grassUDE)
        self.__grassUDE.setPrarieDogUDE(self.__prarieDogUDE)

        self.__grassUDE.setIndependentVarInc(self.__constants.get("TimeIncrement"))
        self.__prarieDogUDE.setIndependentVarInc(self.__constants.get("TimeIncrement"))

        self.__grassUDE.setIV(self.__constants.get("GrassIV"))
        self.__prarieDogUDE.setIV(self.__constants.get("PrarieDogIV"))

    def setResultsFile(self, filePath: str) -> None:
        self.__csvFile.read(filePath)

    def run(self) -> None:
        self.__csvFile.clear()
        for i in range(0,int(self.__constants.get("TimeSpan"))):
            self.__grassUDE.incrementIndependentVar()
            self.__prarieDogUDE.incrementIndependentVar()
            self.__grassUDE.calculateValue()
            self.__prarieDogUDE.calculateValue()
            self.__csvFile.addDataRow(\
                    [self.__grassUDE.getIndependentVar(),\
                    self.__grassUDE.getDependentVar(),\
                    self.__prarieDogUDE.getDependentVar()])
            
            grassPnt=self.__grassUDE.getDataPoint()
            prarieDogPnt=self.__prarieDogUDE.getDataPoint()
            print("Grass:: {0}: {1}  PrarieDog:: {2}: {3}".format(grassPnt.x,grassPnt.y,prarieDogPnt.x,prarieDogPnt.y))

    def getDataPoint(self, time: float):
        tempList=self.__csvFile.lookupDataRow(str(time))
        rv=ThreeDPair()
        if len(tempList)>0:
            rv.x=float(tempList[0])
            rv.y=float(tempList[1])
            rv.z=float(tempList[2])
        return rv

    def save(self) -> None:
        self.__csvFile.write()


def debug() -> None:
    rv=GivenNumbers.debug()
    rv&=CSVFile.debug()
    rv&=UnsolvedDE.debug()
    rv&=GrassUDE.debug()
    rv&=PrarieDogUDE.debug()
    rv&=Simulation.debug()
    print("Debug Successful: {0}".format(rv))


if __name__=="__main__":
    debug()
