library(raster)
library(dhmpr)
# set a demoition matrix
mat <- matrix(c(.53,0,.62,0.195,0.67,0,0,0.13,0.9),nrow = 3,ncol = 3,byrow = TRUE)
colnames(mat) <- rownames(mat) <- c('larvae','juvenile','adult') 
demo <- as.demography(mat)
n_stages <- length(stages(demo))
print(demo)

#set up starting populations
set.seed(42)
xy <- expand.grid(x=seq(145, 150, 0.1), y=seq(-40, -35, 0.1))
Dd <- as.matrix(dist(xy))
w <- exp(-1/nrow(xy) * Dd)
Ww <- chol(w)
xy$z <- t(Ww) %*% rnorm(nrow(xy), 0, 0.1)
coordinates(xy) <- ~x+y
r <- rasterize(xy, raster(points2grid(xy)), 'z')
proj4string(r) <- '+init=epsg:4283'
r[] <- scales::rescale(r[],to=c(0,1))
random_populations <- sampleRandom(r, size=50, na.rm=TRUE, sp=TRUE)
random_populations@data <- as.data.frame(t(rmultinom(50, size = 50, prob = c(0.8,0.2,0.1))))

#set up habitat
features <- list('habitat_suitability_map'=as.habitat_suitability(r),
                 'population'=as.populations(random_populations),
                 'carrying_capacity'=as.carrying_capacity(100))
habitat <- as.habitat(features)
print(habitat)

# set up dispersal parameters.
dispersal_params <- as.dispersal(list(dispersal_distance=list('larvae'=3,'juvenile'=0,'adult'=6),
                dispersal_kernel=list('larvae'=exp(-c(0:2)),'juvenile'=0,'adult'=exp(-c(0:5)*.2)),
                dispersal_proportion=list('larvae'=0.1,'juvenile'=0,'adult'=0.6)))  

## now I've set up a custom function which manipulates rasters (based on a dodgy fire simualtion)
## This will be used as a module to manipulate the habitat suitability between time steps. 
## create a named list with corresponding parameters and values
fire_params <- list(habitat,
                    fire_start_location = sample(ncell(habitat_suitability(habitat)),10),
                    prob = 0.24,
                    continue_to_burn_prob = 0.01)
               
## check to see that it produces a burnt landscape.
hab_dynamics <- as.habitat_dynamics(fire_module,fire_params,check=TRUE)

## now it'll return a habitat_dynamics object which can be used in a simulation/experiment.
hab_dynamics <- as.habitat_dynamics(fire_module,fire_params)
# is.habitat_dynamics(hab_dynamics)
run_habitat_dynamics(hab_dynamics)

# set up a density dependence fucntion. This isn't working as before :( But it should give you some ideas.
ddfun <- function (pop,n) {
  new_pop<-sapply(1:length(pop),function(x)ifelse(pop[x]>n,floor(n * runif(1)),pop[x]))
  return(new_pop)
}

#now we are going to try and set up an experiment using the above functions.
pops_at_time_step <- dispersal_at_time_step <- fire_history_df_list <- fire_at_time_step <- habitat_suit_at_time_step <- list()
pops_at_time_step[[1]] <- populations(habitat) 
habitat_suit_at_time_step[[1]] <- habitat_suitability(habitat) 
fire_at_time_step[[1]] <- run_habitat_dynamics(hab_dynamics)

## begin experiment through time
for(i in 1:n_time_steps){
  
    # need to replace this these next four lines with: dynamic_habitat(fun,attr,params)
    #update the landscape based on last fire. 
    fire_prob <- fire_at_time_step[[i]]/max(fire_at_time_step[[i]][])   
    
    #now you could have some equation on how fire effects underlying habitat suitability. I'm just going to make     # something up :) = habitat_suitability*(1-fire_prob)
    new_hs <- habitat_suitability(habitat)*(1-fire_prob)
    attr(new_hs,"habitat") <- "habitat_suitability" # i need to update attribute inheridence.
    habitat_suit_at_time_step[[i+1]] <- habitat_suitability(habitat) <- new_hs 
    
    # let's disperse people
    dispersed_populations <- dispersal(dispersal_params, habitat, method='ca')
    dispersal_at_time_step[[i]] <- populations(habitat) <- dispersed_populations
    
    ## replaced the bottom few lines with estimate_demography
    pops_at_time_step[[i+1]] <- populations(habitat) <- estimate_demography(demo,habitat)
    
    #now let's start another fire! Mwhahahhaha.
    fire_at_time_step[[i+1]] <- fire_module(habitat,sample(ncell(habitat_suitability(habitat)),10),
      prob = 0.24,
      continue_to_burn_prob = 0.01,
      fire_history = )
}

# #through time
par(mfrow=c(1,3))

larvae_n <- sapply(lapply(pops_at_time_step, "[[", 1)[], function(x)sum(x[]))
plot(larvae_n,type='l',ylab='Total Larvae Abundance',xlab="Time (years)",lwd=2,col='springgreen')

juve_n <- sapply(lapply(pops_at_time_step, "[[", 2)[], function(x)sum(x[]))
plot(juve_n,type='l',ylab='Total Juvenile Abundance',xlab="Time (years)",lwd=2,col='dodgerblue')

adult_n <- sapply(lapply(pops_at_time_step, "[[", 3)[], function(x)sum(x[]))
plot(adult_n,type='l',ylab='Total Adult Abundance',xlab="Time (years)",lwd=2,col='tomato')

