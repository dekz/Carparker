PROJECT_ROOT = File.dirname(__FILE__)
BIN_PATH     = File.join(PROJECT_ROOT, 'bin')
SRC_PATH     = File.join(PROJECT_ROOT, 'src')

BIN = File.join(BIN_PATH, 'carparker')
SRC = File.join(SRC_PATH, '*.c')

desc "Compile"
task :compile => [:clean] do
  puts "\nCompiling Carparker"

  Dir.chdir(PROJECT_ROOT) do
    %x(rm -f #{BIN})
    %x(gcc -Wall -pthread -o #{BIN} #{SRC})
  end
end

desc "Run"
task :run do
  puts "\nRunning carparker"
  exec(BIN)
end

desc "Clean"
task :clean do
  %x(rm -f #{BIN})
end

desc "Compile and run"
task :default => [:compile, :run]