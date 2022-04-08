# Percolation Simulation
This program focuses on percolation theory. In simple terms, it is the finding of the point at which random network is fully connected. For greater detail on the theory, you can check the wikipedia links:   
https://en.wikipedia.org/wiki/Percolation_theory   
https://en.wikipedia.org/wiki/Percolation_threshold

# Running Simulation
`PercolationTest.sln` contains the file structure required to build the project in Visual Studio.
However, you can also use a preferred compiler instead.    

The command to run depends on the OS you use. For windows, it is `PercolationTest.exe 100 20`      
The first value indicates the size of the network. Input 100 generates a network of 10_000 nodes.     
The second value is for the number of trials to run. Input 20 indicates that 20 simulations will be run before results are calculated.

Here's an example of the results after running the program.     
![results](https://user-images.githubusercontent.com/80176765/162432929-cedb79e7-6ce5-4f66-b298-3945c7cd653f.png)


# Model
Percolation theory is applied in practice in various fields. For example, given a composite systems comprised of randomly distributed insulating and metallic materials: what fraction of the materials need to be metallic so that the composite system is an electrical conductor?     
However, this program uses an abstract model, rather than a specific one. Yet, it could be interpreted as per requirements. 

This is a model example:           
![model_example](https://user-images.githubusercontent.com/80176765/162069098-bc008034-6593-42b2-ab51-980faa4dc1a2.png)    
The white/blue cells are open sites. The blue cells are the ones connected to the top. Percolation occurs when the top site connects to the bottom. 


# Calculation

To estimate the percolation threshold = `Os/S` where `Os` is the open sites and `S` is the total size.    
Multiple threads are used to run various simulations at the same time concurrently.   
Then mean is calculated as ![mean](https://user-images.githubusercontent.com/80176765/162213652-dadbcf96-894e-4012-a669-edea10bdf92c.png) where `T` is the number of trials/simulations ran.     
The standard deviation is calculated as ![deviation](https://user-images.githubusercontent.com/80176765/162216912-f8709dbd-3795-41ad-a3b9-5a07a057be0c.jpg) where `Xi` is the result of each simulation, the `x̄` is the mean value and the `T` is the number of simulations. 
Finally, the 95% confidence interval is calculated as ![confidence](https://user-images.githubusercontent.com/80176765/162218021-2c002ba0-c6c3-4960-9bd2-6bd1a3007c0f.jpg) where `z` is a constant value of 1.96, `s` is the standard deviation, and `T` the total size of simulations and `x̄` the mean value.      
For accuracy, at least 50 simulations are required to be run. 

